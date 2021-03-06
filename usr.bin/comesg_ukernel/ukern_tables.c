/*
 * Copyright (c) 2020 Peter S. Blandford-Baker
 * All rights reserved.
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
#include "ukern_mman.h"
#include "ukern_tables.h"
#include "ukern_utils.h"

#include <cheri/cheric.h>
#include <err.h>
#include <errno.h>
#include <sys/mman.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>


coport_tbl_t coport_table;

const int COPORT_TBL_LEN = (MAX_COPORTS*sizeof(coport_tbl_entry_t));

int lookup_port(char * port_name,sys_coport_t ** port_buf)
{
    if(strlen(port_name)>=COPORT_NAME_LEN)
    	err(1,"port name length too long");
    for(int i = 0; i<coport_table.index;i++)
    {
        if(strncmp(port_name,coport_table.table[i].name,COPORT_NAME_LEN)==0)
        {
            *port_buf=coport_table.table[i].port_cap;
            return 0;
        }
    }
    *port_buf=NULL;
    errno=ENOENT;
    return -1;
}


int add_port(coport_tbl_entry_t entry)
{
    int entry_index;
    
    if(coport_table.index==MAX_COPORTS)
    {
        return 1;
    }
    entry_index=atomic_fetch_add(&coport_table.index,1);
    memcpy(&coport_table.table[entry_index],&entry,sizeof(coport_tbl_entry_t));    
    return entry_index;
}

void init_coport_table_entry(coport_tbl_entry_t * entry, sys_coport_t port, const char * name)
{
	coport_tbl_entry_t e;

	e.port=port;
	strncpy(e.name,name,COPORT_NAME_LEN);
	e.id=generate_id();
    e.port_cap=cheri_csetbounds(&port,sizeof(sys_coport_t));

    memcpy(entry,&e,sizeof(coport_tbl_entry_t));
	return;
}

bool in_coport_table(void * __capability addr)
{
    ptrdiff_t table_offset;
    vaddr_t port_addr = (vaddr_t) addr;
    int index;
    if(!cheri_is_address_inbounds(coport_table.table,port_addr))
    {
        printf("address not in bounds\n");
        return false;
    }
    else
    {
        table_offset=port_addr-cheri_getbase(coport_table.table);
        index=table_offset/sizeof(coport_tbl_entry_t);
        if(&coport_table.table[index].port!=addr)
        {
            printf("offset looks wrong\n");
            return false;
        }
    }
    return true;
}

int coport_tbl_setup(void)
{

    coport_table.index=0;
    coport_table.table=ukern_malloc(COPORT_TBL_LEN);
    mlock(coport_table.table,COPORT_TBL_LEN);
    
    /* reserve a superpage or two for this, entries should be small */
    /* reserve a few superpages for ports */
    return 0;
}
