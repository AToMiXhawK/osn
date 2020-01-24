// compile this program with -lpthread flag
// eg: gcc 03_merge_thread_sort.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int ar[10];

typedef struct node {
    int l;
    int r;
} NODE;

void merge(int ar[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m -l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(i=0; i<n1; i++)
        L[i]=ar[l + i];
    for(j=0; j<n2; j++)
        R[j]=ar[m + 1 + j];

    i=0;
    j=0;
    k=l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            ar[k] = L[i];
            i++;
        }
        else
        {
            ar[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
    	ar[k] = L[i];
    	i++;
    	k++;
    }
    while (j < n2)
    {
    	ar[k] = R[j];
    	j++;
    	k++;
    }
}

void *merge_sort(void *a)
{
    NODE *p = (NODE *)a;
    if(p->l < p->r)
    {
        NODE n1, n2;
        int m = (p->l + p->r) / 2;
        pthread_t tid1, tid2;

        n1.l = p->l;
        n1.r = m;

        n2.l = m+1;
        n2.r = p->r;

        pthread_create(&tid1, NULL, merge_sort, &n1);
        pthread_create(&tid2, NULL, merge_sort, &n2);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        merge(ar, p->l, m, p->r);
        pthread_exit(NULL);
    }
}

void print_array(int ar[], int len)
{
	for(int i=0; i<len; i++)
		printf("%d ",ar[i]);
	printf("\n");
}

int main()
{
    int n;
    printf("\nEnter the size of the array (2-10): ");
    scanf("%d",&n);
    printf("\nEnter the elemnts: ");
    for(int i=0; i<n; i++)
    	scanf("%d",&ar[i]);
    printf("\nThe array given is: ");
    print_array(ar,n);

    NODE m;
    m.l = 0;
    m.r = n-1;
    pthread_t tid;

    pthread_create(&tid, NULL, merge_sort, &m);
    pthread_join(tid, NULL);

    printf("\nThe Sorted array is: ");
    print_array(ar,n);
    printf("\n");
    return 0;
}