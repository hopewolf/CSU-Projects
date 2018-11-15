CC = g++
CFLAGS = -Wall -c
LFAGS = -Wall
OBJS = main.o histogram.o
INCLUDE = -I.

PA1 : $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(INCLUDE) -o demo

main.o : main.cpp histogram.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS) 
	
Complex.o : histogram.cpp histogram.h
	$(CC) histogram.cpp $(INCLUDE) $(CFLAGS)
	
# to use make sure to write 'make clean'
clean :
	-rm *.o PA1
