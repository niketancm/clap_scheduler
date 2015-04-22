CC = gcc

CFLAGS = -c

#OBJECTS = list.o list_main.o

#all: list.o list_main.o

my_list:list.o list_main.o
	$(CC) -o my_list list.o list_main.o

list.o:	list.c
	$(CC) $(CFLAGS) -c list.c

list_main.o: list_main.c
	$(CC) $(CFLAGS) -c list_main.c

clean:
	$(RM) my_list *.o
