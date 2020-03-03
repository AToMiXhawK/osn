#include "fcntl.h"           /* For O_* constants */
#include "sys/stat.h"        /* For mode constants */
#include "mqueue.h"
#include <stdio.h>
#include <string.h>
void main() {

    mqd_t q1;
    char str[20];
    int pr;

    q1 = mq_open("/test_q",O_CREAT|O_RDWR,0666,NULL);
    if(q1 == -1) {
     printf("Error");
    }

    while(1)
    {
        printf("\nEnter Message: "); 
        scanf("%s",str); 
        printf("Enter Priority: "); 
        scanf("%d",&pr); 
        if(!strcmp(str,"exit"))
            break;
        mq_send(q1,str,strlen(str),pr);
    }
}

