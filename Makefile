CC=clang++
CFLAGS=-std=c++14 -g -Wall

SOURCES=src/*.cpp
PCH_SOURCE=src/pch.h

OUTFILE=fool

.PHONY: all clean

all:
	make pch
	make build

pch: $(PCH_SOURCE)
	$(CC) $(CFLAGS) -x c++-header $(PCH_SOURCE) -o $(PCH_SOURCE).pch

build: $(PCH_SOURCE).pch $(SOURCES)
	$(CC) $(CFLAGS) -include-pch $(PCH_SOURCE).pch $(SOURCES) -o $(OUTFILE)

clean:
	rm -f $(OUTFILE)
	rm -f $(PCH_SOURCE).pch

