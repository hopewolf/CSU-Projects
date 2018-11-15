CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OBJS = main.o
INCLUDE = -I.

run: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(INCLUDE) -o run

main.o: main.cpp Quagga.h ZooProperty.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)

clean:
	-rm *.o run
