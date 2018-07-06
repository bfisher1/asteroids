CC = gcc
CFLAGS = -Wall -std=c99 -g
OTHERDIR = ./Queue

Asteroids : asteroid.o main.o bullet.o ship.o  util.o object.o graphics.o ./Queue/queue.o
	$(CC) $(CFLAGS) -o $@ $^ -lX11 -lm -I/usr/local/include -L/usr/local/lib -lSDL

object.o : object.c  object.h util.h

asteroid.o : asteroid.c asteroid.h object.h util.h

bullet.o : bullet.c bullet.h util.h

ship.o : ship.c ship.h object.h

util.o : util.c util.h

graphics.o : graphics.c graphics.h

./Queue/queue.o : ./Queue/queue.c ./Queue/queue.h

main.o : main.c asteroid.h ship.h bullet.h util.h object.h graphics.h ./Queue/queue.h

clean:
	rm -f main.o graphics.o util.o ship.o bullet.o asteroid.o object.o Asteroids ./Queue/queue.o