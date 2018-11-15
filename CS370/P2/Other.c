#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int countOther(char sentence[])
{
    int count = 0;
    int isOther;
    char c;
    for(int i=0; sentence[i] != (char)0; ++i) {
        c = sentence[i];
        isOther = ((c >= 32 && c < 64) || (c > 91 && c < 96) || c > 123);
        if (isOther)
            count++;
    }
    return count;
}

int main(int argc, char **argv) {
    printf("Other: I am child with ID %i\n",getpid());
    char* sentence = argv[1];
    return countOther(sentence);
}
