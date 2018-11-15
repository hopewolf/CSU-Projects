C++ = g++
LFLAGS = -o HashTable
CFLAGS = -Wall -I. -g -c

HashTable:	main.o HashTable.o Reader.o
	$(C++) main.o HashTable.o Reader.o $(LFLAGS)

HashTable.o:	HashTable.h HashTable.cpp
	$(C++) HashTable.cpp $(CFLAGS)

Reader.o: Reader.h Reader.cpp HashTable.h
	$(C++) Reader.cpp $(CFLAGS)

main.o:	main.cpp HashTable.h
	$(C++) main.cpp $(CFLAGS)

clean:
	rm -f *.o
	rm -f HashTable
