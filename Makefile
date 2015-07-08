CC=gcc
CFLAGS=-Wall -c -O0 `sdl-config --cflags`
LDFLAGS=`sdl-config --libs`

jenntris: main.o tetris.o graphics.o
	$(CC) main.o tetris.o graphics.o -o ./jenntris $(LDFLAGS)

clean:
	rm -f *.o ./jenntris

