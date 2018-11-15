CC=gcc
DEBUG = -g -I.
CFLAGS =  $(DEBUG) -o
OUT_EXE = PA3 Vowels Consonants Other

build: Initiator.c Vowels.c Consonants.c Other.c
	$(CC) $(CFLAGS) PA3 Initiator.c
	$(CC) $(CFLAGS) Vowels Vowels.c
	$(CC) $(CFLAGS) Consonants Consonants.c
	$(CC) $(CFLAGS) Other Other.c
clean:
	rm -f *.o $(OUT_EXE)
