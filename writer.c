#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 

int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 

    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 

    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
    printf("process id:%d",getpid());
    printf("\nEnter a string : "); 
    scanf("%s",str); 
    printf("String sent: %s\n",str); 
   
    int pid=fork();
    if(pid<0)
        fprintf(stderr,"error");
    else if(pid>0){
        wait(NULL);
        printf("\nTransfer complete\n");
        shmdt(str); 
    }
    else
        execvp("./reader.out",NULL);

    return 0; 
} 