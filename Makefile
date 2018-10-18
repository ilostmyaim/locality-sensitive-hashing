OBJS = lsh.o hash.o LSH.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG)

lsh: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o lsh

lsh.o:
	$(CC) $(CFLAGS) lsh.cpp

hash.o: hash.h hash.cpp
	$(CC) $(CFLAGS) hash.cpp


LSH.o: LSH.h LSH.cpp
	$(CC) $(CFLAGS) LSH.cpp

clean: 
	\rm -f $(OBJS)


