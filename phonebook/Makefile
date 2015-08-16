CC = gcc
CFLAGS = -O2 -Wall
EXECUTABLE = main_origin main_optimal main_hash


default: phonebook.o main_origin.c main_optimal.c
	$(CC) $(CFLAGS) phonebook.o main_origin.c -o main_origin
	$(CC) $(CFLAGS) phonebook.o main_optimal.c -o main_optimal
	$(CC) $(CFLAGS) phonebook.o main_hash.c -o main_hash

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm $(EXECUTABLE) *.o

cleanperf:
	rm perf.*
