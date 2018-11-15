#demo :
#	g++ main.cpp Complex.cpp -I. -o demo

CC = g++
CFLAGS = -Wall -c
LFAGS = -Wall
OBJS = main.o Complex.o
INCLUDE = -I.

demo : $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(INCLUDE) -o demo

main.o : main.cpp Complex.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS) 
	
Complex.o : Complex.cpp Complex.h
	$(CC) Complex.cpp $(INCLUDE) $(CFLAGS)
	
# to use make sure to write 'make clean'
clean :
	-rm *.o demo
