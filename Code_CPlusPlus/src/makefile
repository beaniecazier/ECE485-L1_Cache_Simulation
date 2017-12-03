IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
CFLAGS+=-DLINUX
endif


CacheSim: CacheSim.cpp Cache.cpp Set.cpp Line.cpp
	make clean
	$(CC) -o CacheSim.o CacheSim.cpp Cache.cpp Set.cpp Line.cpp $(CFLAGS)

.PHONY: clean

clean:
	rm -f CacheSim.o
