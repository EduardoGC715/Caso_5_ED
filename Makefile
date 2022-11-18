CC = g++
CFLAGS = -Wall -g

all: main

main:
	$(CC) $(CFLAGS) -o main main.cpp -lcurl