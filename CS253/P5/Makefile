CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OBJS = main.o fRead.o lexo.o StemExcep.o Stem.o
INCLUDE = -I.

PA5 : $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(INCLUDE) -o PA5

main.o : main.cpp fRead.cpp
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)

fRead.o : fRead.cpp fRead.h lexo.cpp StemExcep.cpp
	$(CC) fRead.cpp $(INCLUDE) $(CFLAGS)

lexo.o : lexo.cpp lexo.h Stem.cpp
	$(CC) lexo.cpp $(INCLUDE) $(CFLAGS)

StemExcep.o: StemExcep.cpp StemExcep.h
	$(CC) StemExcep.cpp $(INCLUDE) $(CFLAGS)

Stem.o : Stem.cpp Stem.h
	$(CC) Stem.cpp $(INCLUDE) $(CFLAGS)

clean :
	-rm *.o PA5
