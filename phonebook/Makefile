CC = gcc
CFLAGS = -O1 -Wall -pg
EXECUTABLE = main


default: phonebook.o main.c
	$(CC) $(CFLAGS) phonebook.o main.c -o $(EXECUTABLE)

phonebook.o: phonebook.c phonebook.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm $(EXECUTABLE) *.o gmon.out

