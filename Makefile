OBJS = testnss.o
exe = testnss

CC = gcc
DBG = -W -Wall -g -O0
# Detect os
OS = $(shell uname 2>/dev/null || echo Unknown)
ifeq ($(OS),Darwin)
  # Need pkg-config for macOS
  CFLAGS = $(DBG) $(shell pkg-config --cflags nss)
  LIBS = $(shell pkg-config --libs nss)
else
  # Can skip some libs on Linux since we don't use the entire libnss
  CFLAGS = $(DBG) -I/usr/include/nss -I/usr/include/nspr
  LIBS = -lnss3
endif

$(exe): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJS) $(exe)
