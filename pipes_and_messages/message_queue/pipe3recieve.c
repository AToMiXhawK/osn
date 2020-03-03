#include "fcntl.h"           /* For O_* constants */
#include "sys/stat.h"        /* For mode constants */
#include "mqueue.h"
#include <stdio.h>
#include<stdlib.h>
void main() {

mqd_t q2;
char *buf;
struct mq_attr *attr1;
int prio;
attr1 = malloc(sizeof(struct mq_attr));

q2 = mq_open("/test_q",O_RDWR);

if(q2 == -1) {
 printf("Error");
}

buf = malloc(10*sizeof(char));
mq_getattr(q2, attr1);

mq_receive(q2,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\n Message = %s\n",buf);


mq_receive(q2,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\n Message = %s\n",buf);


mq_receive(q2,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\n Message = %s\n",buf);


mq_receive(q2,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\n Message = %s\n",buf);
}

