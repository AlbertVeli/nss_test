OBJS = testnss.o
exe = testnss

CC = gcc
DBG = -W -Wall -g -O0
#CFLAGS = $(DBG) $(shell pkg-config --cflags nss)
CFLAGS = $(DBG) -I/usr/include/nss -I/usr/include/nspr
LIBS = -lnss3

$(exe): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJS) $(exe)
