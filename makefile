CC=g++
CFLAGS=-I.
DEPS = funkcijos.h
OBJ = main_v2.o mokinys.o funkcijos.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

v2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
