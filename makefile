CC=g++
CFLAGS=-I.

v1: main_v1.o
	$(CC) -o v1 main_v1.o
v2: main_v2.o
	$(CC) -o v2 main_v2.o
