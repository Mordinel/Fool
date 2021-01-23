CC=clang++
CFLAGS=-std=c++17 -g -Wall

SOURCES=src/*.cpp
OUTFILE=fool

.PHONY: all clean

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTFILE)

clean:
	rm -f $(OUTFILE)

