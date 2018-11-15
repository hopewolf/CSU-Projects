#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) 
{
    pid_t Cpid; // pid for vowels, constants, & other
    Cpid=0; // init all pid's to 0
    int count, vCount, cCount, oCount, status;  // counts for iterations and counting chars
    count=0, vCount=0, cCount=0, oCount=0, status=0;  // init all counts to 0
    char sentence[5000];     // char sentence
    
    FILE *f = fopen(argv[1], "r"); // "r" for read
    if(f == NULL) {
        perror ("Error opening file");
        return 1;
    }
    fgets(sentence, 500, f);
        while(count <3) {
            //Vowels fork                   
            if(count == 0) {
                Cpid = fork(); // fork process for Vowels.c
                if(Cpid < 0) {  // error occured
                    fprintf(stderr, "Fork Failed\n");
                    return 1;
                }
                else if(Cpid == 0) { // child process
                    execlp("Vowels","Vowels", sentence, (char*)0); // get the return from vowels
                }
                else {   //parent process
                    printf("Inititator: forked process with ID %i\n", getpid());
                    printf("Inititator: waiting for process [%i]\n",getpid());
                    waitpid(Cpid, &status, 0);
                    vCount = WEXITSTATUS(status);
                    printf("Inititator: child process %i returned %i\n", getpid(), vCount);
                }
            }
            else if(count == 1) {
                Cpid = fork(); // fork process for Consonants
                if(Cpid < 0) {  // error occured
                    fprintf(stderr, "Fork Failed\n");
                    return 1;
                }
                else if(Cpid == 0) { // child process
                    execlp("Consonants","Consonants", sentence, (char*)0);
                }
                else {   //parent process
                    printf("Inititator: waiting for process [%i]\n",getpid());
                    printf("Inititator: forked process with ID %i\n", getpid());
                    waitpid(Cpid, &status, 0);
                    cCount = WEXITSTATUS(status); // get the return from consonants
                    printf("Inititator: child process %i returned %i\n", getpid(), cCount);
                }
            }
            else {
                Cpid = fork(); // fork process for Other
                if(Cpid < 0) {  // error occured
                    fprintf(stderr, "Fork Failed\n");
                    return 1;
                }
                else if(Cpid == 0) { // child process
                    execlp("Other","Other", sentence, (char*)0); // get the return from other
                }
                else {   //parent process
                    printf("Inititator: forked process with ID %i\n", getpid());
                    printf("Inititator: waiting for process [%i]\n",getpid());
                    waitpid(Cpid, &status, 0);
                    oCount = WEXITSTATUS(status);
                    printf("Inititator: child process %i returned %i\n", getpid(), oCount);
                }
            }
            count++;
        }
    printf("The number of vowels is %i\n", vCount);
    printf("The number of consonants is %i\n", cCount);
    printf("The number of other characters is %i\n", oCount);
    fclose(f);  // close the file reader
    return 0;
}

