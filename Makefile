CFLAGS = -std=c99 -pedantic -Wall
CC = gcc

all: blackjack


blackjack.o: blackjack.c
	$(CC) $(CFLAGS) -c blackjack.c -o blackjack.o

game.o: game.c
	$(CC) $(CFLAGS) -c game.c -o game.o

deck.o: deck.c
	$(CC) $(CFLAGS) -c deck.c -o deck.o

blackjack: blackjack.o deck.o game.o
	$(CC) $(CFLAGS) blackjack.o deck.o game.o -o blackjack

clean:
	rm -i blackjack.o deck.o game.o blackjack