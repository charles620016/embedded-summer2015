CC = gcc
CFLAGS = -O2 -Wall
EXECUTABLE = strtok_example strtok_reentrant

default: 
	$(CC) $(CFLAGS) -o strtok_example strtok_example.c
	$(CC) $(CFLAGS) -o strtok_reentrant strtok_reentrant.c

clean:
	rm -f $(EXECUTABLE) *.o