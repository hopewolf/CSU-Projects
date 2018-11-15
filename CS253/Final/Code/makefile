CC = g++ 
CFLAGS = -I. -Wall -O2 -c
LFLAGS = -o Vision

Vision:	main.o Pixel.o
	$(CC) main.o Pixel.o $(LFLAGS)

Pixel.o: Pixel.tpp Pixel.cpp
	$(CC) Pixel.cpp $(CFLAGS)

main.o:	main.cpp Pixel.tpp Image.tpp
	$(CC) main.cpp $(CFLAGS)

# I added this
clean: 
	-rm *.o Vision
