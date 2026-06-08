SOURCE = mjrec.c
OBJECT = test_gf.o rscoder.o rs.o
TARGET = mjgps mjrec
TARGETWIN = mjgpswin mjrecwin

CC = gcc

UNAME_S := $(shell uname -s)

# K&R-era C: relax diagnostics that modern clang / recent gcc treat as errors
# (implicit int, implicit function declarations, etc.).
WARN = -Wno-implicit-int -Wno-implicit-function-declaration \
       -Wno-int-conversion -Wno-return-type

CFLAGS = -O2 -fomit-frame-pointer -pipe -std=gnu89 $(WARN)

# Platform differences:
#   crypt() lives in libc on macOS but needs -lcrypt on Linux/BSD.
#   Static linking (-static) is unsupported on macOS.
ifeq ($(UNAME_S),Darwin)
  CRYPTLIB =
  RECSTATIC =
else
  CRYPTLIB = -lcrypt
  RECSTATIC = -static
endif

#Cygwin version
CWFLAGS = -O2  -mtune=generic -v -fomit-frame-pointer -pipe -lcrypt /bin/cygcrypt-0.dll

LDFLAGS = $(CFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $<

all: $(TARGET)

mjgps: mjgps.h mjgps.c
	$(CC) $(CFLAGS) -o $@ mjgps.c $(CRYPTLIB)
	strip $@

mjrec: mjgps.h mjrec.c
	$(CC) $(CFLAGS) $(RECSTATIC) -o $@ mjrec.c
	strip $@

cygwin: $(TARGETWIN)

mjgpswin: mjgps.h mjgps.c
	$(CC) $(CWFLAGS) -lcrypt -s -o $@ mjgps.c
	strip $@

mjrecwin: mjgps.h mjrec.c
	$(CC) $(CWFLAGS) -s -o $@ mjrec.c
	strip $@

install: all
	install -c -s -g bin -m 700 $(TARGET) /usr/local/games/bin

format:
	indent -bad -bap -bli0 -cdb -psl -sc -ss -i4 *.c
	rm -f *.{c,h}~

clean:
	rm -f $(TARGET) $(OBJECT) *.a *~ *.o *.exe core
