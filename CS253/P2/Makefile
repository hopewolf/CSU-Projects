CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OBJS = main.o fRead.o lexo.o
INCLUDE = -I.

PA2 : $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(INCLUDE) -o PA2

main.o : main.cpp fRead.cpp
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)

fRead.o : fRead.cpp fRead.h
	$(CC) fRead.cpp $(INCLUDE) $(CFLAGS)

lexo.o : lexo.cpp lexo.h
	$(CC) lexo.cpp $(INCLUDE) $(CFLAGS)

clean :
	-rm *.o PA2
