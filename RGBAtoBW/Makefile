CC = gcc-4.8
CFLAGS = -O0 -Wall -fdump-tree-vect-details -ftree-vectorize -mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard
EXECUTABLE = main main_v1 main_v2 main_v3 main_v4 main_v5

default: bmp.o main.c
	$(CC) $(CFLAGS) bmp.o main.c -o main -DORIGIN
	$(CC) $(CFLAGS) bmp.o main.c -o main_v1 -DVERSION1
	$(CC) $(CFLAGS) bmp.o main.c -o main_v2 -DVERSION2
	$(CC) $(CFLAGS) bmp.o main.c -o main_v3 -DVERSION3
	$(CC) $(CFLAGS) bmp.o main.c -o main_v4 -DVERSION4
	$(CC) $(CFLAGS) bmp.o main.c -o main_v5 -DVERSION5

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

run:
	./main
	./main_v1
	./main_v2
	./main_v3
	./main_v4
	./main_v5

clean:
	rm -f $(EXECUTABLE) *.o perf.*

