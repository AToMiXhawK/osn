#include <stdio.h>
#include <unistd.h> 

void main()
{
	int num;
	int fact = 1, x = 1;
	pid_t pid;

	scanf("%d",&num);
	pid = fork();

	if(pid==0){
		printf("\nChild executing\n");
	    for(int i=1;i<=num;i++)	{
	    	fact *=i;
		    printf("%d ",fact);
	    }
        printf("\n");		
	}

	else if(pid>0){
        printf("\nParent executing\n");
	   	for(int i=1;i<=num;i++)
	    	fact *=i;
		
        printf("factorial of %d = %d \n",num,fact);
  	
	}
}