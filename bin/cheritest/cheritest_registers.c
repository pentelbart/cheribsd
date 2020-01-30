/*-
 * Copyright (c) 2012-2018 Robert N. M. Watson
 * Copyright (c) 2014 SRI International
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
#include <sys/sysctl.h>
#include <sys/time.h>

#include <machine/cpuregs.h>
#include <machine/pte.h>
#include <machine/vmparam.h>

#include <cheri/cheri.h>
#include <cheri/cheric.h>

#include <err.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "cheritest.h"

void
test_copyregs(const struct cheri_test *ctp __unused)
{

	__asm__ __volatile__(
	    ".set push\n"
	    ".set noreorder\n"
	    "cgetdefault $c2\n"
	    "cmove $c3, $c2\n"
	    "cmove $c4, $c2\n"
	    "cmove $c5, $c2\n"
	    "cmove $c6, $c2\n"
	    "cmove $c7, $c2\n"
	    ".set pop\n"
	    : : : "$c2", "$c3", "$c4", "$c5", "$c6", "$c7");
	cheritest_success();
}

void
test_listregs(const struct cheri_test *ctp __unused)
{

	/*
	 * Because of the assembly generated by CP2_CR_GET(), can't use a loop
	 * -- register numbers must be available at compile-time.
	 */
	printf("CP2 registers:\n");
	CHERI_CAPREG_PRINT(0);
	CHERI_CAPREG_PRINT(1);
	CHERI_CAPREG_PRINT(2);
	CHERI_CAPREG_PRINT(3);
	CHERI_CAPREG_PRINT(4);
	CHERI_CAPREG_PRINT(5);
	CHERI_CAPREG_PRINT(6);
	CHERI_CAPREG_PRINT(7);
	CHERI_CAPREG_PRINT(8);
	CHERI_CAPREG_PRINT(9);
	CHERI_CAPREG_PRINT(10);
	CHERI_CAPREG_PRINT(11);
	CHERI_CAPREG_PRINT(12);
	CHERI_CAPREG_PRINT(13);
	CHERI_CAPREG_PRINT(14);
	CHERI_CAPREG_PRINT(15);
	CHERI_CAPREG_PRINT(16);
	CHERI_CAPREG_PRINT(17);
	CHERI_CAPREG_PRINT(18);
	CHERI_CAPREG_PRINT(19);
	CHERI_CAPREG_PRINT(20);
	CHERI_CAPREG_PRINT(21);
	CHERI_CAPREG_PRINT(22);
	CHERI_CAPREG_PRINT(23);
	CHERI_CAPREG_PRINT(24);
	CHERI_CAPREG_PRINT(25);
	CHERI_CAPREG_PRINT(26);
	CHERI_PCC_PRINT();
	cheritest_success();
}

/*
 * These tests assume that the compiler and run-time libraries won't muck with
 * the global registers in question -- which is true at the time of writing.
 *
 * However, in the future, it could be that they are modified -- e.g., to
 * differentiate memory capabilities from class-type capabilities.  In that
 * case, these tests would need to check the original capability values saved
 * during process startup -- and also the new expected values.
 */
static void
check_initreg_code(void * __capability c)
{
	uintmax_t v;

	/* Base. */
	v = cheri_getbase(c);
	if (v != CHERI_CAP_USER_CODE_BASE)
		cheritest_failure_errx("base %jx (expected %jx)", v,
		    (uintmax_t)CHERI_CAP_USER_CODE_BASE);

	/* Length. */
	v = cheri_getlen(c);
	if (v > CHERI_CAP_USER_CODE_LENGTH)
		cheritest_failure_errx("length 0x%jx (expected <= 0x%jx)", v,
		    CHERI_CAP_USER_CODE_LENGTH);

	/* Offset. */
	v = cheri_getoffset(c);
	if (v != CHERI_CAP_USER_CODE_OFFSET)
		cheritest_failure_errx("offset %jx (expected %jx)", v,
		    (uintmax_t)CHERI_CAP_USER_CODE_OFFSET);

	/* Type -- should be (-1) for an unsealed capability. */
	v = cheri_gettype(c);
	if (v != 0xffffffffffffffff)
		cheritest_failure_errx("otype %jx (expected %jx)", v,
		    (uintmax_t)0xffffffffffffffff);

	/* Permissions. */
	v = cheri_getperm(c);
	if (v != CHERI_CAP_USER_CODE_PERMS)
		cheritest_failure_errx("perms %jx (expected %jx)", v,
		    (uintmax_t)CHERI_CAP_USER_CODE_PERMS);

	/*
	 * More overt tests for permissions that should -- or should not -- be
	 * there, regardless of consistency with the kernel headers.
	 */
	if ((v & CHERI_PERM_GLOBAL) == 0)
		cheritest_failure_errx("perms %jx (global missing)", v);

	if ((v & CHERI_PERM_EXECUTE) == 0)
		cheritest_failure_errx("perms %jx (execute missing)", v);

	if ((v & CHERI_PERM_LOAD) == 0)
		cheritest_failure_errx("perms %jx (load missing)", v);

	if ((v & CHERI_PERM_STORE) != 0)
		cheritest_failure_errx("perms %jx (store present)", v);

	if ((v & CHERI_PERM_LOAD_CAP) == 0)
		cheritest_failure_errx("perms %jx (loadcap missing)", v);

	if ((v & CHERI_PERM_STORE_CAP) != 0)
		cheritest_failure_errx("perms %jx (storecap present)", v);

	if ((v & CHERI_PERM_STORE_LOCAL_CAP) != 0)
		cheritest_failure_errx("perms %jx (store_local_cap present)",
		    v);

	if ((v & CHERI_PERM_SEAL) != 0)
		cheritest_failure_errx("perms %jx (seal present)", v);

	if ((v & CHERI_PERM_CCALL) == 0)
		cheritest_failure_errx("perms %jx (ccall missing)", v);

	if ((v & CHERI_PERM_UNSEAL) != 0)
		cheritest_failure_errx("perms %jx (unseal present)", v);

	if ((v & CHERI_PERM_SYSTEM_REGS) != 0)
		cheritest_failure_errx("perms %jx (system_regs present)", v);

	if ((v & CHERI_PERMS_SWALL) !=
	    (CHERI_PERMS_SWALL & ~CHERI_PERM_CHERIABI_VMMAP))
		cheritest_failure_errx("perms %jx (expected swperms %x)", v,
		    (CHERI_PERMS_SWALL & ~CHERI_PERM_CHERIABI_VMMAP));

	/* Sealed bit. */
	v = cheri_getsealed(c);
	if (v != 0)
		cheritest_failure_errx("sealed %jx (expected 0)", v);

	/* Tag bit. */
	v = cheri_gettag(c);
	if (v != 1)
		cheritest_failure_errx("tag %jx (expected 1)", v);
	cheritest_success();
}

#ifndef __CHERI_CAPABILITY_TABLE__
static void
check_initreg_data(void * __capability c)
{
	uintmax_t v;

	/* Base. */
	v = cheri_getbase(c);
	if (v != CHERI_CAP_USER_DATA_BASE)
		cheritest_failure_errx("base %jx (expected %jx)", v,
		    (uintmax_t)CHERI_CAP_USER_DATA_BASE);

	/* Length. */
	v = cheri_getlen(c);
	if (v > CHERI_CAP_USER_DATA_LENGTH)
		cheritest_failure_errx("length 0x%jx (expected <= 0x%jx)", v,
		    CHERI_CAP_USER_DATA_LENGTH);

	/* Offset. */
	v = cheri_getoffset(c);
	if (v != CHERI_CAP_USER_DATA_OFFSET)
		cheritest_failure_errx("offset %jx (expected %jx)", v,
		    (uintmax_t)CHERI_CAP_USER_DATA_OFFSET);

	/* Type -- should be (-1) for an unsealed capability. */
	v = cheri_gettype(c);
	if (v != 0xffffffffffffffff)
		cheritest_failure_errx("otype %jx (expected %jx)", v,
		    (uintmax_t)0xffffffffffffffff);

	/* Permissions. */
	v = cheri_getperm(c);
	if (v != CHERI_CAP_USER_DATA_PERMS)
		cheritest_failure_errx("perms %jx (expected %jx)", v,
		    (uintmax_t)CHERI_CAP_USER_DATA_PERMS);

	/*
	 * More overt tests for permissions that should -- or should not -- be
	 * there, regardless of consistency with the kernel headers.
	 */
	if ((v & CHERI_PERM_GLOBAL) == 0)
		cheritest_failure_errx("perms %jx (global missing)", v);

	if ((v & CHERI_PERM_EXECUTE) != 0)
		cheritest_failure_errx("perms %jx (execute present)", v);

	if ((v & CHERI_PERM_LOAD) == 0)
		cheritest_failure_errx("perms %jx (load missing)", v);

	if ((v & CHERI_PERM_STORE) == 0)
		cheritest_failure_errx("perms %jx (store missing)", v);

	if ((v & CHERI_PERM_LOAD_CAP) == 0)
		cheritest_failure_errx("perms %jx (loadcap missing)", v);

	if ((v & CHERI_PERM_STORE_CAP) == 0)
		cheritest_failure_errx("perms %jx (storecap missing)", v);

	if ((v & CHERI_PERM_STORE_LOCAL_CAP) == 0)
		cheritest_failure_errx("perms %jx (store_local_cap missing)",
		    v);

	if ((v & CHERI_PERM_SEAL) != 0)
		cheritest_failure_errx("perms %jx (seal present)", v);

	if ((v & CHERI_PERM_CCALL) == 0)
		cheritest_failure_errx("perms %jx (ccall missing)", v);

	if ((v & CHERI_PERM_UNSEAL) != 0)
		cheritest_failure_errx("perms %jx (unseal present)", v);

	if ((v & CHERI_PERM_SYSTEM_REGS) != 0)
		cheritest_failure_errx("perms %jx (system_regs present)", v);

	if ((v & CHERI_PERMS_SWALL) != CHERI_PERMS_SWALL)
		cheritest_failure_errx("perms %jx (expected swperms %x)", v,
		    CHERI_PERMS_SWALL);

	/* Sealed bit. */
	v = cheri_getsealed(c);
	if (v != 0)
		cheritest_failure_errx("sealed %jx (expected 0)", v);

	/* Tag bit. */
	v = cheri_gettag(c);
	if (v != 1)
		cheritest_failure_errx("tag %jx (expected 1)", v);
	cheritest_success();
}
#endif

void
test_initregs_default(const struct cheri_test *ctp __unused)
{

#ifdef __CHERI_CAPABILITY_TABLE__
	if (cheri_getdefault() == NULL)
		cheritest_success();
	else
		cheritest_failure_errx("Expected NULL $ddc but was %-#p",
		    cheri_getdefault());

#else
	check_initreg_data(cheri_getdefault());
#endif
}

/*
 * Outside of CheriABI, the stack pointer ($sp) is evaluated relative to the
 * default data capability, so no separate stack capability is defined.
 *
 * Inside CheriABI, the stack capability should contain only the specific
 * address range used for the stack.  We could try to capture the same logic
 * here as used in the kernel to select the stack -- but it seems more
 * sensible to simply assert that the capability is not the same as the
 * default capability for the MIPS ABI.
 */
#ifdef __CHERI_PURE_CAPABILITY__

#define CHERI_STACK_OFFSET_MAX 0x7fffff
#define CHERI_STACK_OFFSET_MIN 0x7fc000

void
test_initregs_stack_user_perms(const struct cheri_test *ctp __unused)
{
	register_t v;

	/*
	 * Note: this test is an expected failure since we set VMMAP
	 * TODO: move this into test_initregs_stack once it passes
	 */
	v = cheri_getperm(cheri_getstack());
	if ((v & CHERI_PERMS_SWALL) !=
	    (CHERI_PERMS_SWALL & ~CHERI_PERM_CHERIABI_VMMAP))
		cheritest_failure_errx("perms %jx (expected swperms %x)", v,
		    (CHERI_PERMS_SWALL & ~CHERI_PERM_CHERIABI_VMMAP));
}

void
test_initregs_stack(const struct cheri_test *ctp __unused)
{
	void * __capability c = cheri_getstack();
	register_t v;

	/* Base. */
	v = cheri_getbase(c);
	if (v == CHERI_CAP_USER_DATA_BASE)
		cheritest_failure_errx("base %jx (did not expect %jx)", v,
		    (uintmax_t)CHERI_CAP_USER_DATA_BASE);

	/* Length. */
	v = cheri_getlen(c);
	if (v == CHERI_CAP_USER_DATA_LENGTH)
		cheritest_failure_errx("length 0x%jx (did not expect 0x%jx)",
		    v, CHERI_CAP_USER_DATA_LENGTH);

	/* Offset. */
	v = cheri_getoffset(c);
	if (v > CHERI_STACK_OFFSET_MAX || v < CHERI_STACK_OFFSET_MIN)
		cheritest_failure_errx("stack offset %jx (expected range %jx "
		    "to %jx)", v, (uintmax_t)CHERI_STACK_OFFSET_MIN,
		    (uintmax_t)CHERI_STACK_OFFSET_MIN);

	/* Type -- should be zero for an unsealed capability. */
	v = cheri_gettype(c);
	if (v != -1)
		cheritest_failure_errx("otype %jx (expected %jx)", v,
		    (uintmax_t)0);

	/* Permissions. */
	v = cheri_getperm(c);

	/*
	 * More overt tests for permissions that should -- or should not -- be
	 * there, regardless of consistency with the kernel headers.
	 */
	if ((v & CHERI_PERM_EXECUTE) != 0)
		cheritest_failure_errx("perms %jx (execute present)", v);

	if ((v & CHERI_PERM_LOAD) == 0)
		cheritest_failure_errx("perms %jx (load missing)", v);

	if ((v & CHERI_PERM_LOAD_CAP) == 0)
		cheritest_failure_errx("perms %jx (loadcap missing)", v);

	if ((v & CHERI_PERM_GLOBAL) == 0)
		cheritest_failure_errx("perms %jx (global missing)", v);

	if ((v & CHERI_PERM_STORE) == 0)
		cheritest_failure_errx("perms %jx (store missing)", v);

	if ((v & CHERI_PERM_STORE_CAP) == 0)
		cheritest_failure_errx("perms %jx (storecap missing)", v);

	if ((v & CHERI_PERM_STORE_LOCAL_CAP) == 0)
		cheritest_failure_errx("perms %jx (store_local_cap missing)",
		    v);

	if ((v & CHERI_PERM_SEAL) != 0)
		cheritest_failure_errx("perms %jx (seal present)", v);

	if ((v & CHERI_PERM_SYSTEM_REGS) != 0)
		cheritest_failure_errx("perms %jx (system_regs present)", v);

	if ((v & CHERI_PERM_CCALL) == 0)
		cheritest_failure_errx("perms %jx (ccall missing)", v);

	if ((v & CHERI_PERM_UNSEAL) != 0)
		cheritest_failure_errx("perms %jx (unseal present)", v);

	if (v != CHERI_CAP_USER_DATA_PERMS)
		cheritest_failure_errx("perms %jx (expected %jx)", v,
		    (uintmax_t)CHERI_CAP_USER_DATA_PERMS);

	/* Sealed bit. */
	v = cheri_getsealed(c);
	if (v != 0)
		cheritest_failure_errx("sealed %jx (expected 0)", v);

	/* Tag bit. */
	v = cheri_gettag(c);
	if (v != 1)
		cheritest_failure_errx("tag %jx (expected 1)", v);
	cheritest_success();
}
#endif

void
test_initregs_idc(const struct cheri_test *ctp __unused)
{

#ifndef __CHERI_CAPABILITY_TABLE__
	check_initreg_data(cheri_getidc());
#else
#if __has_builtin(__builtin_mips_cheri_get_captable)
	void* __capability cgp = __builtin_mips_cheri_get_captable();
#else
	/*
	 * XXXAR: this is not guaranteed to work (and in the pc-relative ABI it
	 * will almost certainly be wrong
	 */
	void* __capability cgp = cheri_getidc();
#endif
	uintmax_t perms = cheri_getperm(cgp);
	extern void _CHERI_CAPABILITY_TABLE_;
	void* __capability cap_table = &_CHERI_CAPABILITY_TABLE_;
	/* TODO: this should probably be a preprocessor macro instead */
	_Bool pcrelative_captable = (perms & CHERI_PERM_EXECUTE) != 0;

	CHERITEST_VERIFY(cheri_getlen(cgp) != 0);
	CHERITEST_VERIFY2((perms & CHERI_PERM_STORE) == 0,
	    "perms %jx (store should not be set)", perms);
	CHERITEST_VERIFY2((perms & CHERI_PERM_STORE_CAP) == 0,
	    "perms %jx (store_cap should not be set)", perms);
	CHERITEST_VERIFY2((perms & CHERI_PERM_STORE_LOCAL_CAP) == 0,
	    "perms %jx (store_local_cap should not be set)", perms);
	CHERITEST_VERIFY2((vaddr_t)cap_table == (vaddr_t)cgp,
	    "$cgp (%#p) does not point to _CHERI_CAPABILITY_TABLE_ (%#p)", cgp,
	    cap_table);

	/* XXXAR: pcrelative ABI is a bit different: */
	if (pcrelative_captable) {
		CHERITEST_VERIFY(cheri_getoffset(cgp) != 0);
		void* __capability pcc = cheri_getpcc();
		CHERITEST_VERIFY(cheri_getbase(cgp) == cheri_getbase(pcc));
	} else {
		CHERITEST_VERIFY(cheri_getbase(cgp) != 0);
		CHERITEST_VERIFY(cheri_getbase(cgp) == cheri_getbase(cap_table));
		CHERITEST_VERIFY(cheri_getlen(cgp) == cheri_getlen(cap_table));
		CHERITEST_VERIFY(cheri_getoffset(cgp) == cheri_getoffset(cap_table));
		CHERITEST_VERIFY2((perms & CHERI_PERM_EXECUTE) == 0,
			"perms %jx (execute should not be set)", perms);
	}
#endif
	cheritest_success();
}

void
test_initregs_pcc(const struct cheri_test *ctp __unused)
{
	void * __capability c;

	/* $pcc includes $pc, so clear that for the purposes of the check. */
	c = cheri_getpcc();
	c = cheri_setoffset(c, 0);
	check_initreg_code(c);
}
