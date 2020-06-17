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

int main(int argc, char * const argv[])
{
	pid_t ukern_pid, cochatter_pid;
	setenv("LD_BIND_NOW","yesplease",1);
	char *cochatter_args[5];
	char *comesg_ukernel_args[2]; 


	comesg_ukernel_args[0] = strdup("/usr/bin/comesg_ukernel");
	comesg_ukernel_args[1] = NULL;

	cochatter_args[0] = strdup("/usr/bin/cochatter");
	cochatter_args[1] = strdup("-r24");
	cochatter_args[2] = strdup("-Q");
	cochatter_args[4] = NULL;
	size_t i = 1024;
	int enable_log = 0;
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
	//re-run 931840, 1048576,838656, 798720 
	char * buf_size_str = malloc(14*sizeof(char));
	int cochatter_status;
	if(enable_log)
	{
		if(i==1024)
			i=1;
		for(; i<1024; i*=2)
		{
			memset(buf_size_str,0,10);
			sprintf(buf_size_str,"-b%lu",i);
			cochatter_args[3] = buf_size_str;
			if(!(ukern_pid=fork()))
			{
				//child
				if(execve(comesg_ukernel_args[0],comesg_ukernel_args,environ))
					err(errno,"main:execve failed to execute microkernel");
			}
			sleep(4);
			if(!(cochatter_pid=fork()))
			{

				//child
				if(coexecve(ukern_pid,cochatter_args[0],cochatter_args,environ))
					err(errno,"main:coexecve failed to execute cochatter");
			}	
			waitpid(cochatter_pid,&cochatter_status,WEXITED);
			printf("Done %lu bytes.\n",i);
			kill(ukern_pid,SIGKILL);
		}
		for(i=1024; i<=4096; i+=1024)
		{
			memset(buf_size_str,0,10);
			sprintf(buf_size_str,"-b%lu",i);
			cochatter_args[3] = buf_size_str;
			if(!(ukern_pid=fork()))
			{
				//child
				if(execve(comesg_ukernel_args[0],comesg_ukernel_args,environ))
					err(errno,"main:execve failed to execute microkernel");
			}
			sleep(4);
			if(!(cochatter_pid=fork()))
			{

				//child
				if(coexecve(ukern_pid,cochatter_args[0],cochatter_args,environ))
					err(errno,"main:coexecve failed to execute cochatter");
			}	
			waitpid(cochatter_pid,&cochatter_status,WEXITED);
			printf("Done %lu bytes.\n",i);
			kill(ukern_pid,SIGKILL);
		}
	}
	else
	{
		for(; i<=1048576UL; i+=1024)
		{
			memset(buf_size_str,0,10);
			sprintf(buf_size_str,"-b%lu",i);
			cochatter_args[3] = buf_size_str;
			if(!(ukern_pid=fork()))
			{
				//child
				if(execve(comesg_ukernel_args[0],comesg_ukernel_args,environ))
					err(errno,"main:execve failed to execute microkernel");
			}
			sleep(4);
			if(!(cochatter_pid=fork()))
			{

				//child
				if(coexecve(ukern_pid,cochatter_args[0],cochatter_args,environ))
					err(errno,"main:coexecve failed to execute cochatter");
			}	
			waitpid(cochatter_pid,&cochatter_status,WEXITED);
			printf("Done %lu bytes.\n",i);
			kill(ukern_pid,SIGKILL);
		}
	}
	if(argv)
		return argc;
}