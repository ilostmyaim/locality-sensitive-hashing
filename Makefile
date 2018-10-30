OUT = lsh cube
OBJS = lsh_.o cube_.o LSH.o CUBE.o hash.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG)
HEADERS=$(wildcard *.h)
 
%.o: %.c $(HEADERS)
	$(CC) $(LFLAGS) -c $< -o $@

all: lsh cube

cube: LSH.o CUBE.o hash.o cube_.o
	$(CC) $(LFLAGS) LSH.o CUBE.o hash.o cube_.o -o $@

lsh: LSH.o CUBE.o hash.o lsh_.o
	$(CC) $(LFLAGS) LSH.o CUBE.o hash.o lsh_.o -o $@

clean: 
	rm -rf *.o $(OUT)

