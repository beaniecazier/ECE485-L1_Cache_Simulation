IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

#ODIR=obj
#LDIR =../lib

#LIBS=-lm

#_DEPS = Cache.h Set.h Line.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#_OBJ = CacheSim.o Cache.o Set.o Line.o
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


#$(ODIR)/%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#CacheSim: $(OBJ)
#	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
CFLAGS+=-DLINUX
endif


CacheSim: CacheSim.cpp Cache.cpp Set.cpp Line.cpp
	make clean
	echo $(TARGET)
	$(CC) -o CacheSim.o CacheSim.cpp Cache.cpp Set.cpp Line.cpp $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
