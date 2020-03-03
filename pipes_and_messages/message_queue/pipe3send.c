#include "fcntl.h"           /* For O_* constants */
#include "sys/stat.h"        /* For mode constants */
#include "mqueue.h"
#include <stdio.h>
#include<string.h>
void main() {

mqd_t q1;
char *buf1="hell1";
char *buf2="hello2";
char *buf3="hello3";
char *buf4="hello4";

q1 = mq_open("/test_q",O_CREAT|O_RDWR,0666,NULL);
if(q1 == -1) {
 printf("Error");
}

mq_send(q1,buf1,strlen(buf1),1);
mq_send(q1,buf2,strlen(buf2),2);
mq_send(q1,buf3,strlen(buf3),3);
mq_send(q1,buf4,strlen(buf4),4);

}

