CC = gcc
CFLAGS = -O2 -Wall
EXECUTABLE = main


default: phonebook.o main.c
	$(CC) $(CFLAGS) phonebook.o main.c -o $(EXECUTABLE)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm $(EXECUTABLE) *.o

cleanperf:
	rm perf.*
