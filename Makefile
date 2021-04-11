# Makefile assumes the following \
(1) k.h header file is located in current folder \
(2) kdb+ version >= 3.0 on 64-bit linux (l64) with gcc   \
(3) Q version is 32bit (If not change QVER below to 64   

# Set CFLAG depending on Q version
QVER := 64
ifeq ($(QVER),64)
   CFLAG=-m64
else
   CFLAG=-m32
endif

# Set location of c.o object file to use 
LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
   OBJHOME=l64
else
   OBJHOME=l32
endif

all : int128.so

CC=gcc
OPTS=-D KXVER=3 -Wall -fno-strict-aliasing -Wno-parentheses -g -O2
#LDOPTS=-lpthread
#OBJ=$(OBJHOME)/c.o

%.so: %.c
	$(CC) $(CFLAG) $(OPTS) -shared -fPIC -o $@ $< $(OBJ) $(LDOPTS)

%.s: %.c
	$(CC) $(FLAGS) $(OPTS) -S -fverbose-asm -o $@  $< 

clean:
	rm int128.so