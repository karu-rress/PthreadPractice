CC = gcc

CFLAGS = -Wall -Wextra -pedantic -std=c11

all: 1-deadlock 2-condition

1-deadlock: 1-deadlock.c
	$(CC) $(CFLAGS) 1-deadlock.c -o 1-deadlock

2-condition: 2-condition.c
	$(CC) $(CFLAGS) 2-condition.c -o 2-condition

# 3-semaphore: 3-semaphore.c
# 	$(CC) $(CFLAGS) 3-semaphore.c -o 3-semaphore

4-dining-philosophers: 4-dining-philosophers.c
	$(CC) $(CFLAGS) 4-dining-philosophers.c -o 4-dining-philosophers

5-sequential: 5-sequential.c
	$(CC) $(CFLAGS) 5-sequential.c -o 5-sequential

clean:
	rm 1-deadlock 2-condition 4-dining-philosophers 5-sequential