#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#define READ_END 0
#define WRITE_END 1
#define BUFF_SIZE 1000

int main(int argc, char **argv) 
{
    int fd[2];  // create the pipe
    char buff[10];
    pid_t Cpid; // pid for vowels, constants, & other
    Cpid=0; // init all pid's to 0
    int vCount, cCount, oCount, status;  // counts for iterations and counting chars
    vCount=0, cCount=0, oCount=0, status=0;  // init all counts to 0
    char sentence[256];     // char sentence (file cant be bigger than 255 chars)
    int temp = 10;
    
    // create the pipe, check error
    if(pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }
    
    FILE *f = fopen(argv[1], "r"); // "r" for read
    if(f == NULL) {
        perror ("Error opening file");
        return 1;
    }
    fgets(sentence, 256, f);
    sprintf(buff,"%d", temp);
//    write(fd[1], buff, sizeof(buff)+1);
    Cpid = fork(); // fork process for Vowels.c
    if(Cpid < 0) {  // error occured
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if(Cpid == 0) { // child process
        execlp("Vowels","Vowels", sentence, buff, (char*)0); // get the return from vowels
        write(fd[1], buff, strlen(buff)+1);
    }
    else {   //parent process
        printf("Inititator: forked process with ID %i\n", getpid());
        printf("Inititator: waiting for process [%i]\n",getpid());
        waitpid(Cpid, &status, 0);
        vCount = WEXITSTATUS(status);
        printf("Inititator: child process %i returned %i\n", getpid(), vCount);
    }
//     Cpid = fork(); // fork process for Consonants
//     if(Cpid < 0) {  // error occured
//         fprintf(stderr, "Fork Failed\n");
//         return 1;
//     }
//     else if(Cpid == 0) { // child process
//         execlp("Consonants","Consonants", sentence, (char*)0);
//     }
//     else {   //parent process
//         printf("Inititator: waiting for process [%i]\n",getpid());
//         printf("Inititator: forked process with ID %i\n", getpid());
//         waitpid(Cpid, &status, 0);
//         cCount = WEXITSTATUS(status); // get the return from consonants
//         printf("Inititator: child process %i returned %i\n", getpid(), cCount);
//     }
//     Cpid = fork(); // fork process for Other
//     if(Cpid < 0) {  // error occured
//         fprintf(stderr, "Fork Failed\n");
//         return 1;
//     }
//     else if(Cpid == 0) { // child process
//         execlp("Other","Other", sentence, (char*)0); // get the return from other
//     }
//     else {   //parent process
//         printf("Inititator: forked process with ID %i\n", getpid());
//         printf("Inititator: waiting for process [%i]\n",getpid());
//         waitpid(Cpid, &status, 0);
//         oCount = WEXITSTATUS(status);
//         printf("Inititator: child process %i returned %i\n", getpid(), oCount);
//     }
    printf("The number of vowels is %i\n", vCount);
    printf("The number of consonants is %i\n", cCount);
    printf("The number of other characters is %i\n", oCount);
    fclose(f);  // close the file reader
    return 0;
}

void* create_shared_memory(size_t size) {
    
    // Our memory buffer will be readable and writable:
    int protection = PROT_READ | PROT_WRITE;

    // The buffer will be shared (meaning other processes can access it), but
    // anonymous (meaning third-party processes cannot obtain an address for it),
    // so only this process and its children will be able to use it:
    int visibility = MAP_ANONYMOUS | MAP_SHARED;

    // The remaining parameters to `mmap()` are not important for this use case,
    // but the manpage for `mmap` explains their purpose.
    return mmap(NULL, size, protection, visibility, 0, 0);
    
}

