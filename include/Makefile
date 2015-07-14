#
# 簡易Makefile
#

MAKE	:= make
CC	:= cc
rm	:= rm
CFLAGS	=
SRCS	= file.c memory.c string.c signal.c
OBJS	= $(SRCS:.c=.so)
PKGCFG	:= `pkg-config --cflags --libs glib-2.0`

DEFCFLAGS = -shared -fPIC \
	    $(PKGCFG)

all: $(OBJS)

file.so: file.c
	$(CC) $(DEFCFLAGS) file.c -o file.so

memory.so: memory.c
	$(CC) $(DEFCFLAGS) memory.c -o memory.so

string.so: string.c
	$(CC) $(DEFCFLAGS) string.c -o string.so

signal.so: signal.c
	$(CC) $(DEFCFLAGS) signal.c -o signal.so

.PHONY: clean
clean:
	-$(RM) -f $(OBJS)
