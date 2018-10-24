OUT = lsh cube
OBJS = lsh.o cube.o LSH.o CUBE.o hash.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG)
HEADERS=$(wildcard *.h)
 
%.o: %.c $(HEADERS)
	$(CC) $(LFLAGS) -c $< -o $@

all: lsh cube

cube: LSH.o CUBE.o hash.o cube.o
	$(CC) $(LFLAGS) LSH.o CUBE.o hash.o cube.o -o $@

lsh: LSH.o CUBE.o hash.o lsh.o
	$(CC) $(LFLAGS) LSH.o CUBE.o hash.o lsh.o -o $@

clean: 
	rm -rf *.o $(OUT)

