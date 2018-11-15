#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int countVowels(char sentence[])
{
    int count = 0;
    int isLowercaseVowel, isUppercaseVowel;
    char c;
    for(int i=0; sentence[i] != (char)0; ++i) {
        c = sentence[i];
        // evaluates to 1 (true) if c is an lowercase vowel
        isLowercaseVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
        // evaluates to 1 (true) if c is an uppercase vowel
        isUppercaseVowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
        if (isLowercaseVowel || isUppercaseVowel)
            count++;
    }
    return count;
}

int main(int argc, char **argv) {
    printf("Vowels: I am child with ID %i\n",getpid());
    char* sentence = argv[1];
    return countVowels(sentence);
}
