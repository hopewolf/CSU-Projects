CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
INCLUDE = -I.

all: hanoi.cpp area.cpp main.cpp
	$(CC) $(LFLAGS) $(INCLUDE) hanoi.cpp -o hanoi
	$(CC) $(LFLAGS) $(INCLUDE) area.cpp -o area
	$(CC) $(LFLAGS) $(INCLUDE) main.cpp -o main
