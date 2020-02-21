#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h>

int main() 
{
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0); 
    strcpy(str,"NULL"); 
    while(1)
    {
        printf("\nEnter Message: "); 
        scanf("%s",str); 
        sleep(1);
        if(!strcmp(str,"exit"))
            break;
        strcpy(str,"NULL"); 
    }
    shmdt(str); 
}