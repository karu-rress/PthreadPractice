CC = gcc

CFLAGS = -Wall -Wextra -pedantic -std=c11

all: 1-race 2-atomic 3-mutex 1-race.S 2-atomic.S 3-mutex.S

1-race.S: 1-race.c
	$(CC) $(CFLAGS) 1-race.c -S -o 1-race.S

2-atomic.S: 2-atomic.c
	$(CC) $(CFLAGS) 2-atomic.c -S -o 2-atomic.S

3-mutex.S: 3-mutex.c
	$(CC) $(CFLAGS) 3-mutex.c -S -o 3-mutex.S

1-race: 1-race.c
	$(CC) $(CFLAGS) 1-race.c -o 1-race

2-atomic: 2-atomic.c
	$(CC) $(CFLAGS) 2-atomic.c -o 2-atomic

3-mutex: 3-mutex.c
	$(CC) $(CFLAGS) 3-mutex.c -o 3-mutex

clean:
	rm 1-race{,.S} 2-atomic{,.S} 3-mutex{,.S}
