CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = main.o stem.o
INCLUDE = -I.

demo : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LFLAGS) -o main

main.o : main.cpp stem.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)

stem.o: stem.h stem.cpp
	$(CC) stem.cpp $(INCLUDE) $(CFLAGS)

clean:
	-rm *.o main
