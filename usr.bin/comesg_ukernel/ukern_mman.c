#include <sys/mman.h>
#include <sys/param.h>
#include <cheri/cheric.h>

#include <stdatomic.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

#include "ukern_mman.h"
#include "ukern_params.h"
#include "sys_comsg.h"

buffer_table_t buffer_table;
region_table_t region_table;
work_queue_t jobs_queue;


int reserve_region(void)
{
	void * __capability new_page;

	unsigned int region_index;

	region_table_entry_t entry;
	region_table_entry_t * table;

	pthread_mutex_lock(&region_table.lock);

	table=region_table.table;

	new_page=RESERVE_UKERN(NULL,UKERN_MAP_LEN);
	if(errno!=0)
	{
		err(errno,"mapping region failed\n");
	}
	entry.mem=new_page;
	entry.type=REGION_RESERVED;
	entry.size=UKERN_MAP_LEN;
	entry.free=entry.size;
	pthread_mutex_init(&entry.lock,NULL);
	memcpy(&table[region_table.next],&entry,sizeof(region_table_entry_t));

	region_index=region_table.next++;
	region_table.length++;

	pthread_mutex_unlock(&region_table.lock);
	return region_index;
}

int map_region(void)
{
	void * __capability new_page;

	unsigned int region_index;

	region_table_entry_t entry;

	pthread_mutex_lock(&region_table.lock);

	new_page=MAP_UKERN(NULL,UKERN_MAP_LEN);
	mlock(new_page,UKERN_MAP_LEN);
	if(errno!=0)
	{
		err(errno,"mapping region failed\n");
	}
	entry.mem=new_page;
	entry.type=REGION_MAPPED;
	entry.size=UKERN_MAP_LEN;
	entry.free=entry.size;
	pthread_mutex_init(&entry.lock,NULL);
	memcpy(&region_table.table[region_table.next],&entry,sizeof(region_table_entry_t));

	region_index=region_table.next++;
	region_table.length++;

	pthread_mutex_unlock(&region_table.lock);
	return region_index;
}


int map_reservation(int index)
{
	void * mapped;
	region_table_entry_t * region;

	pthread_mutex_lock(&region_table.lock);
	region = &region_table.table[index];
	printf("region is at %lx\n", cheri_getaddress(region));
	mapped=EXTEND_UKERN(region->mem,region->size);
	// explicitly set offset to make it clear that we use it 
	region->mem=cheri_setoffset(mapped,0);
	region->type=REGION_MAPPED;
	pthread_mutex_unlock(&region_table.lock);
	return 0;
}

int check_region(int entry_index, size_t len)
{
	int error;
	region_table_entry_t * entry = &region_table.table[entry_index];
	pthread_mutex_lock(&entry->lock);
	if(entry->type==REGION_RESERVED)
	{
		error=map_reservation(entry_index);
		if(error!=0)
		{
			err(error,"could not map region at index %d\n",entry_index);
		}
	}
	else if (entry->type==REGION_NONE)
	{
		error=map_region();
		if(error!=0)
		{
			err(error,"could not map region at index %d\n",entry_index);
		}
	}
	if (entry->free>len)
	{
		pthread_mutex_unlock(&entry->lock);
		return true;
	}
	pthread_mutex_unlock(&entry->lock);
	return false;
}

region_table_entry_t * ukern_find_memory(int hint,void ** dest_cap, size_t len)
{
	int i,index,error;
	void * __capability memory;
	int new_offset;
	region_table_entry_t * entry;

	if (len>MAX_BUFFER_SIZE)
	{
		err(1,"currently no support for buffers greater than 1 superpage");
	}
	/* walk the region table for the next region with space*/
	/* if this gets multithreaded this should be write-blocking locks */
	/* this is effectively just a placeholder for now */
	pthread_mutex_lock(&region_table.lock);
	if(region_table.length==0)
	{
		index=map_region();
		entry=&region_table.table[index];
		pthread_mutex_lock(&entry->lock);
		if (check_region(index,len))
		{
			memory=cheri_csetbounds(entry->mem,len);
			//printf("memory1 perms: %lx\n",cheri_getperm(memory));
			memory=cheri_andperm(memory,BUFFER_PERMS);
			//printf("memory2 perms: %lx\n",cheri_getperm(memory));
			new_offset=cheri_getoffset(entry->mem)+len;
			entry->mem=cheri_setoffset(entry->mem,new_offset);
			entry->free=entry->free-len;

			pthread_mutex_unlock(&entry->lock);
			pthread_mutex_unlock(&region_table.lock);
			*dest_cap=memory;
			return entry;
		}
		pthread_mutex_unlock(&entry->lock);
	}
	else
	{
		for (i = 0; i < region_table.length; ++i)
		{
			index=(i+hint)%region_table.length;
			entry=&region_table.table[index];
			if(entry->type==REGION_NONE)
			{
				error=map_region();
				if(error!=index)
				{
					err(1,"region mapping error");
				}
			}
			pthread_mutex_lock(&entry->lock);
			if (check_region(index,len))
			{
				memory=cheri_csetbounds(entry->mem,len);
				//printf("memory1 perms: %lx\n",cheri_getperm(memory));
				memory=cheri_andperm(memory,BUFFER_PERMS);
				//printf("memory2 perms: %lx\n",cheri_getperm(memory));
				new_offset=cheri_getoffset(entry->mem)+len;
				entry->mem=cheri_setoffset(entry->mem,new_offset);
				entry->free=entry->free-len;

				pthread_mutex_unlock(&entry->lock);
				pthread_mutex_unlock(&region_table.lock);
				*dest_cap=memory;
				return entry;
			}
			pthread_mutex_unlock(&entry->lock);
		}
	}
	pthread_mutex_unlock(&region_table.lock);
	return NULL;
}


int map_new_region(void)
{
	int index, error;
	pthread_mutex_lock(&region_table.lock);
	index=reserve_region();
	error=map_reservation(index);
	pthread_mutex_unlock(&region_table.lock);
	return index;
}

void * get_buffer_memory(region_table_entry_t ** region_dst,size_t len)
{
	int region_idx;
	void * buffer;
	region_table_entry_t * region;

	region_idx=region_table.next;
	region=ukern_find_memory(region_idx,&buffer,len);
	if (buffer==NULL)
	{
		err(1,"unknown memory allocation error\n");
	}

	*region_dst=region;
	return buffer;
}

void * buffer_malloc(size_t len)
{
	int buffer_idx;
	buffer_table_entry_t buf_entry;
	region_table_entry_t * region;

	buf_entry.mem=get_buffer_memory(&region,len);
	buf_entry.region=region;
	buf_entry.type=BUFFER_ACTIVE;

	pthread_mutex_lock(&buffer_table.lock);
	buffer_table.table[buffer_table.next]=buf_entry;
	buffer_idx=buffer_table.next++;
	pthread_mutex_unlock(&buffer_table.lock);
	return buf_entry.mem;
}

void * buffer_free(void * __capability buf)
{
	/* just a placeholder really */
	/* later i want to add facility to reuse/clean up old buffers */
	buffer_table_entry_t buf_entry;
	pthread_mutex_lock(&buffer_table.lock);
	for (int i = 0; i < buffer_table.length; ++i)
	{
		if (buf==buffer_table.table[i].mem)
		{
			buf_entry=buffer_table.table[i];
			if(buf_entry.type==BUFFER_ACTIVE)
			{
				buf_entry.type=BUFFER_FREED;
			}
		}
	}
	pthread_mutex_unlock(&buffer_table.lock);
	return cheri_cleartag(buf);
}

int buffer_table_setup(void)
{
	pthread_mutexattr_t mtx_attr;
	pthread_mutexattr_init(&mtx_attr);
	pthread_mutexattr_settype(&mtx_attr,PTHREAD_MUTEX_RECURSIVE);
	
	buffer_table.length=0;
	buffer_table.next=0;
	buffer_table.table=calloc(MAX_COPORTS*U_FUNCTIONS*WORKER_COUNT*MAX_COMUTEXES,sizeof(buffer_table_entry_t));

	return pthread_mutex_init(&buffer_table.lock,&mtx_attr);
}

int region_table_setup(void)
{
	pthread_mutexattr_t mtx_attr;
	pthread_mutexattr_init(&mtx_attr);
	pthread_mutexattr_settype(&mtx_attr,PTHREAD_MUTEX_RECURSIVE);
	
	region_table.length=0;
	region_table.next=0;
	region_table.table=calloc(MAX_COPORTS*2,sizeof(region_table_entry_t));

	return pthread_mutex_init(&region_table.lock,&mtx_attr);
}

int work_queue_setup(int len)
{
	int error;
	pthread_mutexattr_t mtx_attr;
	pthread_condattr_t cond_attr;

	pthread_mutexattr_init(&mtx_attr);
	pthread_condattr_init(&cond_attr);

	jobs_queue.end=-1; //first item will move to position 0 
	jobs_queue.start=0;
	jobs_queue.count=0;
	jobs_queue.items=calloc(len,sizeof(work_queue_item_t));
	jobs_queue.max_len=len;

	error=pthread_mutex_init(&jobs_queue.lock,&mtx_attr);
	error+=pthread_cond_init(&jobs_queue.not_empty,&cond_attr);
	error+=pthread_cond_init(&jobs_queue.not_full,&cond_attr);
	return error;
}

work_queue_item_t * queue_put_job(work_queue_t * queue,work_queue_item_t * job)
{
	work_queue_item_t * q_job;
	pthread_mutex_lock(&queue->lock);
	while(queue->count==queue->max_len)
	{
		pthread_cond_wait(&queue->not_full,&queue->lock);
	}
	queue->end=(queue->end+1)%queue->max_len;
	queue->items[queue->end]=*job;
	q_job=&queue->items[queue->end];
	queue->count+=1;
	pthread_cond_signal(&queue->not_empty);
	pthread_mutex_unlock(&queue->lock);
	return q_job;
}

work_queue_item_t * queue_get_job(work_queue_t * queue)
{
	work_queue_item_t * job;
	pthread_mutex_lock(&queue->lock);
	while(queue->count==0)
	{
		pthread_cond_wait(&queue->not_empty,&queue->lock);
	}
	job=&queue->items[queue->start];
	queue->start=(queue->start+1)%queue->max_len;
	queue->count-=1;
	pthread_cond_signal(&queue->not_full);
	pthread_mutex_unlock(&queue->lock);
	return job;
}

void * ukern_malloc(size_t length)
{
	work_queue_item_t malloc_job;
	_Atomic(work_queue_item_t *) q_job;
	pthread_mutexattr_t mtx_attr;
	pthread_condattr_t cond_attr;
	void * __capability memory;

	if(length<=0)
	{
		err(1,"cannot request buffer of length less than 1");
	}
	else if (length>UKERN_MAP_LEN)
	{
		err(1,"cannot request buffer or length greater than UKERN_MAP_LEN");
	}

	pthread_mutexattr_init(&mtx_attr);
	pthread_condattr_init(&cond_attr);

	malloc_job.action=BUFFER_ALLOCATE;
	malloc_job.len=length;
	malloc_job.subject=NULL;

	pthread_mutex_init(&malloc_job.lock,&mtx_attr);
	pthread_cond_init(&malloc_job.processed,&cond_attr);

	pthread_mutex_lock(&malloc_job.lock);
	//same lock as q_job
	q_job=queue_put_job(&jobs_queue,&malloc_job);	
	while(q_job->subject==NULL)
	{
		//printf("waiting for job completion...\n");
		pthread_cond_wait(&q_job->processed,&q_job->lock);
	}
	memory=q_job->subject;
	pthread_mutex_unlock(&q_job->lock);
	return memory;
}

void * ukern_mman(void *args)
{
	int error;
	work_queue_item_t * task;

	if(args!=NULL)
	{
		warn("ukern_mman takes no args");
	}
	error=work_queue_setup((WORKER_COUNT*U_FUNCTIONS)+2);
	error+=buffer_table_setup();
	error+=region_table_setup();
	if (error!=0)
	{
		err(1,"queue/table setup failed\n");
	}
	task=NULL;
	for (;;)
	{
		task=queue_get_job(&jobs_queue);
		if (task==NULL)
		{
			err(1,"no task returned");
		}
		pthread_mutex_lock(&task->lock);
			switch (task->action)
		{
			case BUFFER_ALLOCATE:
				task->subject=buffer_malloc(task->len);
				break;
			case BUFFER_FREE:
				task->subject=buffer_free(task->subject);
				break;
			default:
				err(1,"invalid operation %d specified",task->action);
		}
		if(task->subject==NULL)
		{
			err(1,"could not assign buffer");
		}
		pthread_cond_signal(&task->processed);
		pthread_mutex_unlock(&task->lock);
		
	}
}