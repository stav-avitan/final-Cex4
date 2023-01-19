CC=gcc
FLAGS = -Wall -g

all: output

output: main.o graph.o nodes.o edges.o
	$(CC) $(FLAGS) $^ -o $@

main.o: main.c
	$(CC) $(FLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

nodes.o: nodes.c nodes.h
	$(CC) $(FLAGS) -c nodes.c

edges.o: edges.c edges.h
	$(CC) $(FLAGS) -c edges.c


.PHONY: all clean
clean:
	rm -f *.o output