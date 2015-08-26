CC = gcc
CFLAGS = -O2 -Wall
EXECUTABLE = main main_v1 main_v2


default: bmp.o main.c
	$(CC) $(CFLAGS) bmp.o main.c -o main -DORIGIN
	$(CC) $(CFLAGS) bmp.o main.c -o main_v1 -DVERSION1

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE) *.o perf.*

