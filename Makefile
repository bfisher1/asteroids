CC = gcc
CFLAGS = -Wall -std=c99 -g

Asteroids : asteroid.o main.o bullet.o ship.o  util.o object.o graphics.o
	$(CC) $(CFLAGS) -o $@ $^ -lX11 -lm -I/usr/local/include -L/usr/local/lib -lSDL

object.o : object.c  object.h util.h

asteroid.o : asteroid.c asteroid.h object.h

bullet.o : bullet.c bullet.h

ship.o : ship.c ship.h object.h

util.o : util.c util.h

graphics.o : graphics.c graphics.h

main.o : main.c asteroid.h ship.h bullet.h util.h object.h graphics.h

clean:
	rm -f main.o graphics.o util.o ship.o bullet.o asteroid.o object.o Asteroids