
#include "ukern_msg_malloc.h"
#include "ukern_mman.h"

#include <stddef.h>
#include <pthread.h>
#include <sys/mman.h>
#include <cheri/cheric.h>
#include <cheri/cherireg.h>
#include <sys/sched.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <stdatomic.h>
#include <time.h>
#include <stdio.h>

const size_t max_len = 1024*1024;

struct {
	_Atomic(void * __capability) current_message_pool;
	_Atomic(void * __capability) next_message_pool;
	pthread_cond_t need_new_mem;
} mem_tbl;
#define MSG_POOL_TOP (cheri_getbase(mem_tbl.current_message_pool)+cheri_getlen(mem_tbl.current_message_pool))

static
void map_msg_region(void)
{
	void * __capability new_page;
	new_page=MAP_UKERN(NULL,UKERN_MAP_LEN*48);
	memset(new_page,0,UKERN_MAP_LEN*48);
	//mlock(new_page,UKERN_MAP_LEN*30);
	if(errno!=0)
	{
		err(errno,"mapping region failed\n");
	}
	atomic_store(&mem_tbl.next_message_pool,new_page);
	return;
}


static
void get_new_mem(void)
{
	int i = 1;
	while(atomic_load(&mem_tbl.next_message_pool)==NULL)
	{
		//printf("spinning\n");
		if(i%100==0)
			sched_yield();
		i++;
	}
	atomic_store(&mem_tbl.current_message_pool,mem_tbl.next_message_pool);
	atomic_store(&mem_tbl.next_message_pool,NULL);
}

void *map_new_mem(void*args)
{
	struct timespec sleepytime;
	
	map_msg_region();
	atomic_store(&mem_tbl.current_message_pool,mem_tbl.next_message_pool);
	mem_tbl.next_message_pool=NULL;
	for(;;)
	{
		if(mem_tbl.next_message_pool==NULL)
			map_msg_region();
		sleepytime.tv_sec=20;
		sleepytime.tv_nsec=0;
		nanosleep(&sleepytime,&sleepytime);
	}
	return args;
}

void * __capability get_mem
(size_t len)
{
	void * __capability result;
	void * __capability reduced_pool;
	void * __capability orig_pool;
	size_t new_len;
	vaddr_t base, new_base;
	size_t j;
	if (len>max_len)
		err(EINVAL,"may not allocate more than %lu", max_len);
	
	orig_pool = mem_tbl.current_message_pool;
	len=CHERI_REPRESENTABLE_LENGTH(len);
	do {
		if (len>cheri_getlen(orig_pool))
		{
			get_new_mem();
			orig_pool = mem_tbl.current_message_pool;
		}
		//align on len
		if((len & (len-1))==0)
		{
			base=(cheri_getbase(orig_pool) + len - 1) & -len;
		}
		else
		{
			base=(((cheri_getbase(orig_pool) + len - 1) / len) * len);
		}
		result=cheri_setaddress(orig_pool,base);
		result=cheri_setboundsexact(result,len);
		new_len=cheri_gettop(orig_pool)-cheri_gettop(result);
		new_base=CHERI_REPRESENTABLE_BASE(cheri_gettop(result),new_len);
		j=1;
		while(new_base<cheri_gettop(result)-1) //shrink the len until the capabilities do not overlap
		{
			j++;
			new_len=cheri_gettop(orig_pool)-(cheri_gettop(result)+(j*2));
			new_base=CHERI_REPRESENTABLE_BASE(cheri_gettop(result)+(j*2),new_len);
		}
		reduced_pool=cheri_setaddress(orig_pool,new_base);
		reduced_pool=cheri_setboundsexact(reduced_pool,cheri_getlen(reduced_pool)-cheri_getoffset(reduced_pool));
	} while(!atomic_compare_exchange_strong_explicit(&mem_tbl.current_message_pool,&orig_pool,reduced_pool,memory_order_acq_rel,memory_order_acquire));
	if(cheri_getlen(mem_tbl.current_message_pool)<UKERN_MAP_LEN*4)
	{
		atomic_store(&mem_tbl.current_message_pool,atomic_load(&mem_tbl.next_message_pool));
		atomic_store(&mem_tbl.next_message_pool,NULL);

	}
	return result;
}

