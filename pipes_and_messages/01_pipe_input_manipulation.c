#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    int pipefds1[2], pipefds2[2];
    int returnstatus1, returnstatus2;
    int pid;
    int buf_size = 128;
    char pipe1writemessage[buf_size];
    char read_data[buf_size];
    char file_data[buf_size];
    FILE *fptr;
    int fd;

    returnstatus1 = pipe(pipefds1);
    if (returnstatus1 == -1) {
        printf("Unable to create pipe 1 \n");
        return 1;
    }

    returnstatus2 = pipe(pipefds2);
    if (returnstatus2 == -1) {
        printf("Unable to create pipe 2 \n");
        return 1;
    }

    printf("Enter a multi line string( press ';' to end input)\n");
    scanf("%[^;]s", pipe1writemessage);

    pid = fork();
    if (pid != 0){ // Parent process 
        close(pipefds1[0]); // Close the unwanted pipe1 read side
        close(pipefds2[1]); // Close the unwanted pipe2 write side
        printf("\nParent: Writing to pipe 1: \n%s\n", pipe1writemessage);
        write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage));
        
        read(pipefds2[0], read_data, sizeof(read_data));
        printf("\nParent: Reading from pipe 2: \n%s\n", read_data);

        close(pipefds1[1]);
        close(pipefds2[0]);
    } 
   
    else{ //child process
        close(pipefds1[1]); // Close the unwanted pipe1 write side
        close(pipefds2[0]); // Close the unwanted pipe2 read side
        read(pipefds1[0], read_data, sizeof(read_data));

        int c_count=0, w_count=0, l_count=0;
        if(strlen(read_data)>0)
        {   w_count++;  l_count++;  }

        for(int i = 0; i < strlen(read_data); i++){
        if(read_data[i] != ' ' && read_data[i] != '\n')  
            c_count++;
        
        if((read_data[i] == ' ' || read_data[i] == '\n' || read_data[i] == '\0') && read_data[i+1]!='\0')
            w_count++;

        if(read_data[i] == '\n' && read_data[i+1]!='\0')
            l_count++;
        }
        
        fptr = fopen("counts.txt", "w");
        fprintf(fptr,"Character Count: %d\n",c_count);
        fprintf(fptr,"Word Count: %d\n",w_count);
        fprintf(fptr,"Line Count: %d\n",l_count);
        fclose(fptr);

        fd = open("counts.txt", O_RDONLY);
        read(fd, file_data, buf_size);
        write(pipefds2[1], file_data, sizeof(file_data));
        close(pipefds1[0]);
        close(pipefds2[1]);
    }
    return 0;
}