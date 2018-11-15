CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall -lgtest -lpthread
OBJS = test_main.o test_portAlg.o ../PA4
INCLUDE = -I../

test_all: $(OBJS)
	$(CC) $(LFLAGS) $(INLUDE) $(OBJS) -o testALL

test_main.o: test_main.cpp
	$(CC) $(CFLAGS) $(INCLUDE) test_main.cpp

test_portAlg.o: test_portAlg.cpp
	$(CC) $(CFLAGS) $(INCLUDE) test_portAlg.cpp
