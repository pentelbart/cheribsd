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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

extern char **environ;

int main(int argc,  char * const argv[])
{
	pid_t ipc_pid;
	setenv("LD_BIND_NOW","yesplease",1);
	char *ipc_args[10];
	int enable_log = 0;

	ipc_args[0] = strdup("/usr/bin/ipc");
	ipc_args[1] = strdup("-r16");
	ipc_args[2] = strdup("-q");
	ipc_args[4] = strdup("-S");
	ipc_args[8] = strdup("2thread");
	ipc_args[7] = strdup("-B");
	ipc_args[9] = NULL;
	size_t i = 1024;
	int opt;
	char * strptr;
	/*
	int receive = 0;
	
	int explicit = 0;*/
	while((opt=getopt(argc,argv,"b:e"))!=-1)
	{
		switch(opt)
		{
			case 'b':
				i = strtol(optarg, &strptr, 10);
				if (*optarg == '\0' || *strptr != '\0' || i <= 0)
					err(1,"invalid start buf size");
				break;
			case 'e':
				enable_log = 1;
				break;
			default:
				break;
		
		}
	}
	//continue at 999424 bytes (pipe).
	char * buf_size_str = malloc(20*sizeof(char));
	int ipc_status;
	if (enable_log && i<=1024)
	{
		if(i==1024)
			i=1;
		for(; i<1024; i*=2)
		{
			memset(buf_size_str,0,20);
			sprintf(buf_size_str,"-b %lu",i);

			ipc_args[3] = strdup(buf_size_str);
			ipc_args[5] = strdup("-ipipe");
			sprintf(buf_size_str,"-t %lu",i);
			ipc_args[6] = strdup(buf_size_str);
			for(size_t j = 0; j<14; j++)
			{
				if(!(ipc_pid=fork()))
				{

					//child
					if(execve(ipc_args[0],ipc_args,environ))
						err(errno,"main:execve failed to execute ipc");
				}	
				waitpid(ipc_pid,&ipc_status,WEXITED);
			}
			printf("Done %lu bytes (pipe).\n",i);
			ipc_args[5] = strdup("-ilocal");
			for(size_t j = 0; j<14; j++)
			{
				if(!(ipc_pid=fork()))
				{

					//child
					if(execve(ipc_args[0],ipc_args,environ))
						err(errno,"main:execve failed to execute ipc");
				}	
				waitpid(ipc_pid,&ipc_status,WEXITED);
			}
			printf("Done %lu bytes (local).\n",i);
		}
		i=1024;
	}
	for(; i<=1048576UL; i+=1024)
	{
		memset(buf_size_str,0,20);
		sprintf(buf_size_str,"-b %lu",i);

		ipc_args[3] = strdup(buf_size_str);
		memset(buf_size_str,0,20);
		sprintf(buf_size_str,"-t %lu",i);
		ipc_args[6] = strdup(buf_size_str);
		ipc_args[5] = strdup("-ipipe");
		for(size_t j = 0; j<14; j++)
		{
			if(!(ipc_pid=fork()))
			{

				//child
				if(execve(ipc_args[0],ipc_args,environ))
					err(errno,"main:execve failed to execute ipc");
			}	
			waitpid(ipc_pid,&ipc_status,WEXITED);
		}
		printf("Done %lu bytes (pipe).\n",i);
		ipc_args[5] = strdup("-ilocal");
		for(size_t j = 0; j<14; j++)
		{
			if(!(ipc_pid=fork()))
			{

				//child
				if(execve(ipc_args[0],ipc_args,environ))
					err(errno,"main:execve failed to execute ipc");
			}	
			waitpid(ipc_pid,&ipc_status,WEXITED);
		}
		printf("Done %lu bytes (local)\n",i);
	}

	if(argv)
		return argc;
}