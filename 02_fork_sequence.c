#include <stdio.h>
#include <sys/wait.h> 
#include <unistd.h> 
#include <stdlib.h>

void main()
{	 
	pid_t pid;
	pid = fork();

	if(pid ==0){
		pid_t pid1 = fork();
		if(pid1==0){
			pid_t pid2 = fork();
			if(pid2 ==0){
				printf("third child \n");
				exit(0);
			}
			else{
				wait(NULL);
				printf("second child \n");
		            	exit(0);
		    }
		}
		else{
			wait(NULL);
			printf("first child \n");
			exit(0);
		} 
	}
	else{
	    wait(NULL);
		printf("parent\n");		
	}
}