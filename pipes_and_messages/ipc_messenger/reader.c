#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> 
#include <unistd.h>
#include <string.h>

int main() 
{
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);

    while(1)
    {
        if(!strcmp(str,"NULL"))
            continue;
        if(!strcmp(str,"exit"))
            break; 
        printf("\nMessage Recieved: %s\n",str);
        sleep(2);
    }

    shmdt(str);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}