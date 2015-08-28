CC = gcc
CFLAGS = -O0 -Wall
EXECUTABLE = main main_v1 main_v2


default: bmp.o main.c
	$(CC) $(CFLAGS) bmp.o main.c -o main -DORIGIN
	$(CC) $(CFLAGS) bmp.o main.c -o main_v1 -DVERSION1
	$(CC) $(CFLAGS) bmp.o main.c -o main_v2 -DVERSION2
	$(CC) $(CFLAGS) bmp.o main.c -o main_v3 -DVERSION3

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

run:
	./main
	./main_v1
	./main_v2
	./main_v3

clean:
	rm -f $(EXECUTABLE) *.o perf.*

