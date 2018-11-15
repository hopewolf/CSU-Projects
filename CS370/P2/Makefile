CC=gcc
DEBUG = -g -I.
CFLAGS =  $(DEBUG) -o
OUT_EXE = PA2 Vowels Consonants Other

build: Initiator.c Vowels.c Consonants.c Other.c
	$(CC) $(CFLAGS) PA2 Initiator.c
	$(CC) $(CFLAGS) Vowels Vowels.c
	$(CC) $(CFLAGS) Consonants Consonants.c
	$(CC) $(CFLAGS) Other Other.c
clean:
	rm -f *.o $(OUT_EXE)
