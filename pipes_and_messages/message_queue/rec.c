#include "fcntl.h"           /* For O_* constants */
#include "sys/stat.h"        /* For mode constants */
#include "mqueue.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    mqd_t q2;
    char *buf;
    struct mq_attr *attr1;
    int pr;
    attr1 = malloc(sizeof(struct mq_attr));

    q2 = mq_open("/test_q",O_RDWR);

    if(q2 == -1) {
     printf("Error");
    }

    buf = malloc(32*sizeof(char));
    mq_getattr(q2, attr1);

    while(1){
        int opt;
        printf("\nEnter option:\n\t1. Fetch from Queue\n\t2. Exit\n: ");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                    mq_receive(q2,buf,attr1->mq_msgsize,&pr);
                    printf("Priority= %d",pr);
                    printf("\nMessage = %s\n",buf);
                    break;
            case 2:
                    printf("Thakyou!!\n");
                    return 0;
                    break;
            default:
                    printf("Invalid Input!!\n");
        }
    }
    

}

