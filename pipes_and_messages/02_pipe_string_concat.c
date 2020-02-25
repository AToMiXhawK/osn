#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipefds1[2], pipefds2[2];
    int returnstatus1, returnstatus2;
    int pid;
    int buf_size = 128;
    char pipe1writemessage[buf_size];
    char read_data[buf_size];
    char file_data[buf_size];
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

    printf("Enter a string: ");
    scanf("%s", pipe1writemessage);

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

        FILE *fptr = fopen("concat.txt", "w");
        char *hello = "Hello ";
        fprintf(fptr, hello);
        fprintf(fptr, read_data, sizeof(read_data));
        fclose(fptr);

        fd = open("concat.txt", O_RDONLY);
        read(fd, file_data, buf_size);
        write(pipefds2[1], file_data, sizeof(file_data));
        close(fd);
        close(pipefds1[0]);
        close(pipefds2[1]);
    }
}

