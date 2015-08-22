CC = gcc
CFLAGS = -O2 -Wall
EXECUTABLE = example strtok_reentrant

default: 
	$(CC) $(CFLAGS) -o example example.c
	$(CC) $(CFLAGS) -o strtok_reentrant strtok_reentrant.c

clean:
	rm -f $(EXECUTABLE) *.o