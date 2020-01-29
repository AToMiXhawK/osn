#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int r1,c1,r2,c2;
int A[4][4], B[4][4], C[4][4];

struct args
{
	int i;
    int j;
};

void *multiply(void *a)
{
	struct args *p = a;
	int sum=0;
	for(int k=0;k<r2;k++)
		sum += A[p->i][k] * B[k][p->j];
	C[p->i][p->j] = sum;
	pthread_exit(0);
}

int main()
{
    srand(time(0));
    r1 = rand()%3+2; c1 = rand()%3+1; r2 = c1; c2 = rand()%3+2;
    pthread_t thread[r1*c2];
    int tid = 0;

    for(int i=0; i<r1; i++)
		for(int j=0; j<c1; j++)
            A[i][j] = rand()%5;

    for(int i=0; i<r2; i++)
		for(int j=0; j<c2; j++)
            B[i][j] = rand()%5;

    printf("Array A:\n");
    for(int i=0; i<r1; i++)
		{ for(int j=0; j<c1; j++) printf("%d\t",A[i][j]); printf("\n"); }
    
    printf("\nArray B:\n");
    for(int i=0;i<r2;i++)
		{ for(int j=0;j<c2;j++) printf("%d\t",B[i][j]); printf("\n"); }

    for(int i=0; i<r1; i++)
		for(int j=0;j<c2;j++)
        {
            struct args *p = (struct args*) malloc(sizeof(struct args));
            p->i = i;
            p->j = j;
            pthread_create(&thread[tid++],NULL,multiply,(void *)p);
        }
    
    for(int i=0; i<tid; i++)
		pthread_join(thread[i],NULL);

    printf("\nProduct:\n");
    for(int i=0; i<r1; i++)
		{ for(int j=0; j<c2; j++) printf("%d\t",C[i][j]); printf("\n"); }

    return 0;
}