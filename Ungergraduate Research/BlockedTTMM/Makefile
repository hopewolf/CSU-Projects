CFLAGS=-O3 -std=c99
LIBRARIES=-lm
CC?=gcc
OBJS = BlockedTTMM.o 
all: plain check

debug: CFLAGS =-DDEBUG -g -Wall -Wextra -std=c99
debug: all
		
plain: $(OBJS)
	$(CC) BlockedTTMM-wrapper.c -o BlockedTTMM $(OBJS) $(CFLAGS) $(LIBRARIES)

check: $(OBJS)
	$(CC) BlockedTTMM-wrapper.c -o BlockedTTMM.check $(OBJS) $(CFLAGS) $(LIBRARIES) -DCHECKING

verify: $(OBJS) BlockedTTMM_verify.o
	$(CC) BlockedTTMM-wrapper.c -o BlockedTTMM.verify $(OBJS) BlockedTTMM_verify.o $(CFLAGS) $(LIBRARIES) -DVERIFY

verify-rand: $(OBJS) BlockedTTMM_verify.o
	$(CC) BlockedTTMM-wrapper.c -o BlockedTTMM.verify-rand $(OBJS) BlockedTTMM_verify.o $(CFLAGS) $(LIBRARIES) -DVERIFY -DRANDOM

BlockedTTMM.o : BlockedTTMM.c
	$(CC) BlockedTTMM.c -o BlockedTTMM.o $(CFLAGS) -c

BlockedTTMM_verify.o : BlockedTTMM_verify.c
	$(CC) BlockedTTMM_verify.c -o BlockedTTMM_verify.o $(CFLAGS) -c

clean:
	rm -f *.o BlockedTTMM BlockedTTMM.check BlockedTTMM.verify BlockedTTMM.verify-rand
