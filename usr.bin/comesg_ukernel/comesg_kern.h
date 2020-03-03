#ifndef _COMESG_KERN
#define _COMESG_KERN

#include <pthread.h>

#include "coport.h"
#include "sys_comsg.h"
#include "sys_comutex.h"
#include "ukern_params.h"


typedef struct _worker_args_t 
{
	char name[LOOKUP_STRING_LEN];
	void * __capability cap;
} worker_args_t;

typedef struct _worker_map_entry_t
{
	char func_name[LOOKUP_STRING_LEN];
	worker_args_t workers[WORKER_COUNT];
} worker_map_entry_t;

typedef struct _request_handler_args_t
{
	char func_name[LOOKUP_STRING_LEN];
} request_handler_args_t;

typedef struct _coport_tbl_entry_t
{
	unsigned int id;
	char name[COPORT_NAME_LEN];
	unsigned int status;
	coport_t port;
} coport_tbl_entry_t;

typedef struct _coport_tbl_t
{
	coport_tbl_entry_t table[MAX_COPORTS];
	pthread_mutex_t lock;
	int index;
} coport_tbl_t;

typedef struct _comutex_tbl_entry_t
{
	unsigned int id;
	sys_comutex_t mtx;
} comutex_tbl_entry_t;

typedef struct _comutex_tbl_t
{
	int index;
	comutex_tbl_entry_t table[MAX_COMUTEXES];
	pthread_mutex_t lock;
} comutex_tbl_t;


int generate_id(void);
int rand_string(char * buf,unsigned int len);
int add_port(coport_tbl_entry_t * entry);
int add_mutex(comutex_tbl_entry_t * entry);
int lookup_port(char * port_name,coport_t ** port_buf);
int lookup_mutex(char * mtx_name,sys_comutex_t ** mtx_buf);
void update_worker_args(worker_args_t * args, const char * function_name);
void *coport_open(void *args);
void *comutex_setup(void *args);
void *comutex_lock(void *args);
void *comutex_unlock(void *args);
int comutex_deinit(comutex_tbl_entry_t * m);
void *manage_requests(void *args);
int coaccept_init(
	void * __capability * __capability  code_cap,
	void * __capability * __capability  data_cap, 
	char * target_name,
	void * __capability * __capability target_cap);
int coport_tbl_setup(void);
int comutex_tbl_setup(void);
int spawn_workers(void * func, pthread_t * threads, const char * name);
void run_tests(void);
int main(int argc, const char *argv[]);


extern coport_tbl_t coport_table;
extern comutex_tbl_t comutex_table;

#endif