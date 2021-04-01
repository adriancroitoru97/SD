CC=gcc
CFLAGS=-Wall -Wextra -std=c99

TARGETS=main

build: $(TARGETS)

main: main.c cdll.c operations.c
	$(CC) $(CFLAGS) main.c cdll.c operations.c -o main

clean:
	rm -f $(TARGETS)