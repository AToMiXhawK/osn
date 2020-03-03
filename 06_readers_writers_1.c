#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "queue.h"

#define max 6
int data = 0, rc = 0;
struct Queue *q;
struct QNode *qn;
sem_t mutex,wrt;

void *reader(void *arg)
{
    srand(time(0));
    int id = *((int *) arg);
    FILE *f;
    while(1)
    {
        int t = (rand()%5)+3;
        sem_wait(&mutex);
        rc++;
        if(rc==1)
            sem_wait(&wrt);
        sem_post(&mutex);
        
        printf("Reader %d reads %d from the file\n",id,data);
        
        sem_wait(&mutex);
        rc--;
        if(rc==0)
            sem_post(&wrt);
        sem_post(&mutex);    
        sleep(t);
    }
    pthread_exit(0);
}

void *writer(void *arg)
{
    srand(time(0));
    int id = *((int *) arg);
    FILE *f;
    while(1)
    {
        int t = (rand()%3)+5;
		printf("Writer %d arrived",id);
		if(!isQueueEmpty(q))
			printf(", Waiting in write queue\n");
		else
			printf("\n");
		enQueue(q, id);
		printQueue(q);
        int ret = sem_trywait(&wrt);
		if(ret==-1){
			printf("Writer %d tries to write\n",id);
			sem_wait(&wrt);
		}
		
        f = fopen("Object.txt","w");
        sleep(1);
        int rd = rand()%10;
		data = rd;
        printf("Data writen by the writer %d is %d\n",id,data);
        sem_post(&wrt);
		qn = deQueue(q);
		printQueue(q);
        sleep(t);
    }
    pthread_exit(0);
}

int main()
{
    srand(time(0));
	q = createQueue();
    int id[max],i;
    FILE *f;
    pthread_t rtid[max],wtid[max];;
    sem_init(&wrt,0,1);
    sem_init(&mutex,0,1);

    f = fopen("Object.txt","w");
    int n = rand();
    fprintf(f,"%d",n);
    fclose(f);
	for(i=0; i<3; i++)
  	{
    	pthread_create(&wtid[i],NULL,writer,(void *) &i);
    	//printf("Writer %d created\n",i);
    	pthread_create(&rtid[i],NULL,reader,(void *) &i);
    	//printf("Reader %d created\n",i);
	}
    
	for(i=0; i<3; i++)
        pthread_join(wtid[i],NULL);
		pthread_join(rtid[i],NULL);
    return 0;
}