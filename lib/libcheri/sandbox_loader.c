/*-
 * Copyright (c) 2012-2015 Robert N. M. Watson
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract (FA8750-10-C-0237)
 * ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>

#if !__has_feature(capabilities)
#error "This code requires a CHERI-aware compiler"
#endif

#include <sys/types.h>
#include <sys/param.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <machine/cheri.h>
#include <machine/cheric.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <libgen.h>
#include <sandbox_stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cheri_class.h"
#include "cheri_invoke.h"
#include "cheri_system.h"
#include "cheri_type.h"
#include "libcheri_stat.h"
#include "sandbox.h"
#include "sandbox_elf.h"
#include "sandbox_internal.h"
#include "sandbox_methods.h"
#include "sandboxasm.h"

#define	roundup2(x, y)	(((x)+((y)-1))&(~((y)-1))) /* if y is powers of two */

#define	GUARD_PAGE_SIZE	0x1000
#define	METADATA_SIZE	0x1000
#define	STACK_SIZE	(32*PAGE_SIZE)

CHERI_CLASS_DECL(libcheri_system);

int
sandbox_class_load(struct sandbox_class *sbcp)
{
	__capability void *codecap;
	size_t length;
	ssize_t max_prog_offset;
	int saved_errno;
	caddr_t base;

	/*
	 * Set up the code capability for a new sandbox class.  Very similar
	 * to object setup (i.e., guard pages for NULL, etc), but no need to
	 * configure a stack.
	 *
	 * Eventually, we will want to do something a bit different here -- in
	 * particular, perform run-time-linker-esque setup such as vtable
	 * initialisation, and also set up the code and data capabilities
	 * quite differently.
	 */

	length = sbcp->sbc_sandboxlen;
	base = sbcp->sbc_mem = mmap(NULL, length, PROT_NONE, MAP_ANON, -1, 0);
	if (sbcp->sbc_mem == MAP_FAILED) {
		saved_errno = errno;
		warn("%s: mmap region", __func__);
		goto error;
	}
	if ((max_prog_offset = sandbox_loadelf64(sbcp->sbc_fd, base, length,
	    SANDBOX_LOADELF_CODE)) == -1) {
		saved_errno = errno;
		goto error;
	}

	/*
	 * Protect guard page(s) at the bottom of the code capability.
	 *
	 * XXXRW: More ideally, the ELF load wouldn't unprotect them.  See
	 * XXXBD in sandbox_object_load().
	 */
	if (mprotect(base, SANDBOX_METADATA_BASE, PROT_NONE) < 0) {
		saved_errno = errno;
		warn("%s: mprotect NULL guard page", __func__);
		goto error;
	}

	/*
	* Parse the sandbox ELF binary for CCall methods provided and
	* required.
	*/
	if (sandbox_parse_ccall_methods(sbcp->sbc_fd,
	     &sbcp->sbc_provided_methods, &sbcp->sbc_required_methods) < 0) {
		saved_errno = EINVAL;
		warnx("%s: sandbox_parse_ccal_methods() failed for %s",
		    __func__, sbcp->sbc_path);
		goto error;
	}

	/*
	 * Construct various class-related capabilities, such as the type,
	 * code capability for the run-time linker, and code capability for
	 * object-capability invocation.
	 */
	sbcp->sbc_typecap = cheri_type_alloc();

	codecap = cheri_ptrperm(sbcp->sbc_mem, max_prog_offset,
	    CHERI_PERM_GLOBAL | CHERI_PERM_LOAD | CHERI_PERM_EXECUTE);
	codecap = cheri_setoffset(codecap, SANDBOX_RTLD_VECTOR);
	sbcp->sbc_classcap_rtld = cheri_seal(codecap, sbcp->sbc_typecap);

	codecap = cheri_ptrperm(sbcp->sbc_mem, max_prog_offset,
	    CHERI_PERM_GLOBAL | CHERI_PERM_LOAD | CHERI_PERM_EXECUTE);
	codecap = cheri_setoffset(codecap, SANDBOX_INVOKE_VECTOR);
	sbcp->sbc_classcap_invoke = cheri_seal(codecap, sbcp->sbc_typecap);

	codecap = cheri_ptrperm(sbcp->sbc_mem, max_prog_offset,
	    CHERI_PERM_GLOBAL | CHERI_PERM_LOAD | CHERI_PERM_EXECUTE);
	if (sandbox_create_method_vtable(codecap, sbcp->sbc_provided_methods,
	    (void __capability *__capability *__capability *)&sbcp->sbc_vtable) == -1) {
		saved_errno = EINVAL;
		warnx("%s: sandbox_create_method_vtable", __func__);
		goto error;
	}

	return (0);

error:
	if (sbcp->sbc_mem != NULL)
		munmap(sbcp->sbc_mem, sbcp->sbc_sandboxlen);
	errno = saved_errno;
	return (-1);
}

void
sandbox_class_unload(struct sandbox_class *sbcp)
{

	munmap(sbcp->sbc_mem, sbcp->sbc_sandboxlen);
}

static struct cheri_object
cheri_system_object_for_instance(struct sandbox_object *sbop)
{
	struct cheri_object system_object;
	__capability void *codecap, *datacap;

	/*
	 * Construct an object capability for the system-class instance that
	 * will be passed into the sandbox.
	 *
	 * The code capability will simply be our $pcc.
	 *
	 * XXXRW: For now, we will populate $c0 with $pcc on invocation, so we
	 * need to leave a full set of permissions on it.  Eventually, we
	 * would prefer to limit this to LOAD and EXECUTE.
	 *
	 * XXXRW: We should do this once per class .. or even just once
	 * globally, rather than on every object creation.
	 */
	codecap = cheri_getpcc();
	codecap = cheri_setoffset(codecap,
	    (register_t)CHERI_CLASS_ENTRY(libcheri_system));
	system_object.co_codecap = cheri_seal(codecap, cheri_system_type);

	/*
	 * Construct a data capability describing the sandbox structure
	 * itself, which allows the system class to identify the sandbox a
	 * request is being issued from.  Embed saved $c0 as first field to
	 * allow the ambient MIPS environment to be installed.
	 */
	datacap = cheri_ptrperm(sbop, sizeof(*sbop), CHERI_PERM_GLOBAL |
	    CHERI_PERM_LOAD | CHERI_PERM_LOAD_CAP | CHERI_PERM_STORE |
	    CHERI_PERM_STORE_CAP | CHERI_PERM_STORE_LOCAL_CAP);
	system_object.co_datacap = cheri_seal(datacap, cheri_system_type);

	/*
	 * Return object capability.
	 *
	 * XXXRW: Possibly, this should be !CHERI_PERM_GLOBAL -- but we do not
	 * currently support invoking non-global objects.
	 */
	return (system_object);
}

int
sandbox_object_load(struct sandbox_class *sbcp, struct sandbox_object *sbop)
{
	__capability void *datacap;
	struct sandbox_metadata *sbmp;
	size_t length;
	ssize_t max_prog_offset;
	int saved_errno;
	caddr_t base;

	/*
	 * Perform an initial reservation of space for the sandbox, but using
	 * anonymous memory that is neither readable nor writable.  This
	 * ensures there is space for all the various segments we will be
	 * installing later.
	 *
	 * The rough sandbox memory map is as follows:
	 *
	 * K + 0x1000 [stack]
	 * K          [guard page]
	 * J + 0x1000 [heap]
	 * J          [guard page]
	 *  +0x600      Reserved vector
	 *  +0x400      Reserved vector
	 *  +0x200      Object-capability invocation vector
	 *  +0x0        Run-time linker vector
	 * 0x8000     [memory mapped binary]
	 * 0x2000     [guard page]
	 * 0x1000     [read-only sandbox metadata page]
	 * 0x0000     [guard page]
	 *
	 * Address constants in sandbox.h must be synchronised with the layout
	 * implemented here.  Location and contents of sandbox metadata is
	 * part of the ABI.
	 */
	length = sbcp->sbc_sandboxlen;
	base = sbop->sbo_mem = mmap(NULL, length, PROT_NONE, MAP_ANON, -1, 0);
	if (sbop->sbo_mem == MAP_FAILED) {
		saved_errno = errno;
		warn("%s: mmap region", __func__);
		goto error;
	}

	/*
	 * Map and (eventually) link the program.  It may overlap guard pages,
	 * etc so lower ones will be reconfigured manually.
	 */
	if ((max_prog_offset = sandbox_loadelf64(sbcp->sbc_fd, base, length,
	    SANDBOX_LOADELF_DATA)) == -1) {
		saved_errno = errno;
		goto error;
	}

	/*
	 * Zero and protect guard page(s) to the base of the metadata
	 * structure.
	 */
	/*
	 * XXXBD: Object binary should not cover map these, but currently
	 * this is the ELF header.
	 */
	if (mprotect(base, SANDBOX_METADATA_BASE, PROT_NONE) < 0) {
		saved_errno = errno;
		warn("%s: mprotect NULL guard page", __func__);
		goto error;
	}

	/*
	 * Skip guard page(s) to the base of the metadata structure.
	 */
	base += SANDBOX_METADATA_BASE;
	length -= SANDBOX_METADATA_BASE;

	/*
	 * Map metadata structure -- but can't fill it out until we have
	 * calculated all the other addresses involved.
	 */
	if ((sbmp = mmap(base, METADATA_SIZE, PROT_READ | PROT_WRITE,
	    MAP_ANON | MAP_FIXED, -1, 0)) == MAP_FAILED) {
		saved_errno = errno;
		warn("%s: mmap metadata", __func__);
		goto error;
	}
	base += roundup2(METADATA_SIZE, PAGE_SIZE);
	length -= roundup2(METADATA_SIZE, PAGE_SIZE);

	/*
	 * Protect post-metadata guard page(s)
	 */
	if (mprotect(base, SANDBOX_BINARY_BASE - roundup2(SANDBOX_METADATA_BASE +
	    METADATA_SIZE, PAGE_SIZE), PROT_NONE) < 0) {
		saved_errno = errno;
		warn("%s: mprotect binary guard page", __func__);
		goto error;
	}

	/*
	 * Assert that we didn't bump into the sandbox entry address.  This
	 * address is hard to change as it is the address used in static
	 * linking for sandboxed code.
	 */
	assert((register_t)base - (register_t)sbop->sbo_mem <
	    SANDBOX_BINARY_BASE);

	/*
	 * Skip already mapped binary.
	 */
	base = (caddr_t)sbop->sbo_mem + roundup2(max_prog_offset, PAGE_SIZE);
	length = sbcp->sbc_sandboxlen - roundup2(max_prog_offset, PAGE_SIZE);

	/*
	 * Skip guard page.
	 */
	base += GUARD_PAGE_SIZE;
	length -= GUARD_PAGE_SIZE;

	/*
	 * Heap.
	 */
	sbop->sbo_heapbase = (register_t)base - (register_t)sbop->sbo_mem;
	sbop->sbo_heaplen = length - (GUARD_PAGE_SIZE + STACK_SIZE);
	if (mmap(base, sbop->sbo_heaplen, PROT_READ | PROT_WRITE,
	    MAP_ANON | MAP_FIXED, -1, 0) == MAP_FAILED) {
		saved_errno = errno;
		warn("%s: mmap heap", __func__);
		goto error;
	}
	memset(base, 0, sbop->sbo_heaplen);
	base += sbop->sbo_heaplen;
	length -= sbop->sbo_heaplen;

	/*
	 * Skip guard page.
	 */
	base += GUARD_PAGE_SIZE;
	length -= GUARD_PAGE_SIZE;

	/*
	 * Stack.
	 */
	if (mmap(base, length, PROT_READ | PROT_WRITE, MAP_ANON | MAP_FIXED,
	    -1, 0) == MAP_FAILED) {
		saved_errno = errno;
		warn("%s: mmap stack", __func__);
		goto error;
	}
	memset(base, 0, length);
	base += STACK_SIZE;
	length -= STACK_SIZE;

	/*
	 * There should not be too much, nor too little space remaining.  0
	 * is our Goldilocks number.
	 */
	assert(length == 0);

	/*
	 * Now that addresses are known, write out metadata for in-sandbox use.
	 */
	sbmp->sbm_heapbase = sbop->sbo_heapbase;
	sbmp->sbm_heaplen = sbop->sbo_heaplen;

	if (sbcp->sbc_sandbox_class_statp != NULL) {
		(void)sandbox_stat_object_register(
		    &sbop->sbo_sandbox_object_statp,
		    sbcp->sbc_sandbox_class_statp,
		    SANDBOX_OBJECT_TYPE_POINTER, (uintptr_t)sbop->sbo_mem);
		SANDBOX_CLASS_ALLOC(sbcp->sbc_sandbox_class_statp);
	}

	/*
	 * Construct data capability for run-time linker vector.
	 */
	datacap = cheri_ptrperm(sbop->sbo_mem, sbcp->sbc_sandboxlen,
	    CHERI_PERM_GLOBAL | CHERI_PERM_LOAD | CHERI_PERM_LOAD_CAP |
	    CHERI_PERM_STORE | CHERI_PERM_STORE_CAP |
	    CHERI_PERM_STORE_LOCAL_CAP);
	sbop->sbo_cheri_object_rtld.co_codecap = sbcp->sbc_classcap_rtld;
	sbop->sbo_cheri_object_rtld.co_datacap = cheri_seal(datacap,
	    sbcp->sbc_typecap);

	/*
	 * Construct data capability for object-capability invocation vector.
	 */
	datacap = cheri_ptrperm(sbop->sbo_mem, sbcp->sbc_sandboxlen,
	    CHERI_PERM_GLOBAL | CHERI_PERM_LOAD | CHERI_PERM_LOAD_CAP |
	    CHERI_PERM_STORE | CHERI_PERM_STORE_CAP |
	    CHERI_PERM_STORE_LOCAL_CAP);
	if (sandbox_set_provided_method_variables(datacap,
	    sbcp->sbc_provided_methods)
	    == -1) {
		saved_errno = EINVAL;
		warnx("%s: sandbox_set_ccallee_method_variables", __func__);
		goto error;
	}
	if (sandbox_set_required_method_variables(datacap,
	    sbcp->sbc_required_methods)
	    == -1) {
		saved_errno = EINVAL;
		warnx("%s: sandbox_set_ccaller_method_variables", __func__);
		goto error;
	}
	/*
	 * XXXBD: Ideally we would render the .CHERI_CCALLEE and
	 * .CHERI_CCALLER sections read-only at this point to avoid
	 * control flow attacks.
	 */
	sbop->sbo_cheri_object_invoke.co_codecap = sbcp->sbc_classcap_invoke;
	sbop->sbo_cheri_object_invoke.co_datacap = cheri_seal(datacap,
	    sbcp->sbc_typecap);

	/*
	 * Install a reference to the system object in the class.
	 *
	 */
	sbmp->sbm_system_object = sbop->sbo_cheri_object_system =
	    cheri_system_object_for_instance(sbop);

	/*
	 * Protect metadata now that we've written all values.
	 */
	if (mprotect(sbmp, METADATA_SIZE, PROT_READ) < 0) {
		saved_errno = errno;
		warn("%s: mprotect metadata", __func__);
		goto error;
	}
	return (0);

error:
	if (sbop->sbo_mem != NULL)
		munmap(sbop->sbo_mem, sbcp->sbc_sandboxlen);
	errno = saved_errno;
	return (-1);
}

void
sandbox_object_unload(struct sandbox_class *sbcp, struct sandbox_object *sbop)
{

	munmap(sbop->sbo_mem, sbcp->sbc_sandboxlen);
}

void *
sandbox_object_getbase(struct sandbox_object *sbop)
{

	return (sbop->sbo_mem);
}

size_t
sandbox_class_getlength(struct sandbox_class *sbcp) 
{

	return (sbcp->sbc_sandboxlen);
}
