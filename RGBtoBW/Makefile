CC = gcc
CFLAGS = -O2 -Wall
EXECUTABLE = main


default: bmp.o
	$(CC) $(CFLAGS) bmp.o main.c -o main

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE) *.o perf.*

