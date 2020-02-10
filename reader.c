//Compile this as gcc reader.c -o reader.out to execute it in writer program

#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> 
#include<unistd.h>

int main() 
{ 
    // ftok to generate unique key 
    printf("\n\nprocess id:%d",getpid());
    key_t key = ftok("shmfile",65); 
    
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("\nData read from memory: %s\n",str); 
      
    //detach from shared memory  
    shmdt(str); 
    
    // destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL); 
     
    return 0; 
} 