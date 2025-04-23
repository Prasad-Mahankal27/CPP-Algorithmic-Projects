#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define BUFFER_SIZE 100

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent to child!";
    char read_msg[BUFFER_SIZE];

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid > 0) { // Parent Process
       
        close(fd[0]); // Close unused read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]); // Close write end after writing
    } 
    else { // Child Process

        close(fd[1]);
        read(fd[0], read_msg, BUFFER_SIZE);
        close(fd[0]);

        // Redirect output to a file
        int file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file_fd < 0) {
            perror("File open failed");
            return 1;
        }
        dup2(file_fd, STDOUT_FILENO);
        close(file_fd);
        
        // Redirect input from a file (if needed)
        int input_fd = open("input.txt", O_RDONLY);
        if (input_fd >= 0) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        
        // Print
        printf("Child received: %s\n", read_msg);
        fprintf(stderr, "This is an error message\n");
    }
    return 0;
}
