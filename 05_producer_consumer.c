#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t *producers;
pthread_t *consumers;

sem_t mutex,empty,full;

int *buf, buf_pos=-1, prod_count, con_count, buf_len;

int produce(pthread_t self){
	int i = 0;
	int p = 1 + rand()%40;
	while(!pthread_equal(*(producers+i),self) && i < prod_count)
		i++;
	printf("\nProducer %d produced %d \n\n",i+1,p);
	return p;
}

void consume(int p,pthread_t self){
	int i = 0;
	while(!pthread_equal(*(consumers+i),self) && i < con_count)
		i++;
	printf("Buffer:");
	for(i=0;i<=buf_pos;++i)
		printf("%d ",*(buf+i));
	printf("\nConsumer %d consumed %d \nCurrent buffer len: %d\n\n",i+1,p,buf_pos);
}

void print_buf_full()
{
	printf("Cannot Insert to Buffer, Buffer is full\n");
}

void print_buf_empty()
{
	printf("Buffer is Empty, Cannot Consume.\n");
}

void* producer(void *args){
	while(1){
		int p = produce(pthread_self());
		++buf_pos;
		if(buf_pos>=buf_len)
		{
			print_buf_full();
			sleep(3 + rand()%3);
			--buf_pos;
			continue;
		}
		sem_wait(&empty);
		sem_wait(&mutex);
		*(buf + buf_pos) = p; 
		sem_post(&mutex);
		sem_post(&full);
		sleep(1 + rand()%3);
	}
	return NULL;
}


void* consumer(void *args){
	int c;
	while(1){
		if(buf_pos<=-1)
		{
			print_buf_empty();
			sleep(3 + rand()%4);
			continue;
		}
		sem_wait(&full);
		sem_wait(&mutex);
		c = *(buf+buf_pos);
		consume(c,pthread_self());
		--buf_pos;
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1+rand()%5);
	}
	return NULL;
}

int main(void){
	
	int i,err;
	srand(time(NULL));

	sem_init(&mutex,0,1);
	sem_init(&full,0,0);

	printf("Enter the number of Producers: ");
	scanf("%d",&prod_count);
	producers = (pthread_t*) malloc(prod_count*sizeof(pthread_t));

	printf("Enter the number of Consumers: ");
	scanf("%d",&con_count);
	consumers = (pthread_t*) malloc(con_count*sizeof(pthread_t));

	printf("Enter buffer capacity: ");
	scanf("%d",&buf_len);
	buf = (int*) malloc(buf_len*sizeof(int));

	sem_init(&empty,0,buf_len);

	for(i=0;i<prod_count;i++){
		err = pthread_create(producers+i,NULL,&producer,NULL);
		if(err != 0){
			printf("Error creating producer %d: %s\n",i+1,strerror(err));
		}else{
			printf("Successfully created producer %d\n",i+1);
		}
	}

	for(i=0;i<con_count;i++){
		err = pthread_create(consumers+i,NULL,&consumer,NULL);
		if(err != 0){
			printf("Error creating consumer %d: %s\n",i+1,strerror(err));
		}else{
			printf("Successfully created consumer %d\n",i+1);
		}
	}

	for(i=0;i<prod_count;i++){
		pthread_join(*(producers+i),NULL);
	}
	for(i=0;i<con_count;i++){
		pthread_join(*(consumers+i),NULL);
	}

	return 0;
}