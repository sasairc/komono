#
# 簡易Makefile
#

MAKE	:= make
CC	:= cc
rm	:= rm
CFLAGS	=
SRCS	= file.c memory.c string.c signal.c
OBJS	= $(SRCS:.c=.so)
PKGCFG	= `pkg-config --cflags --libs glib-2.0`

DEFCFLAGS = -shared -fPIC \
	$(PKGCFG)

all: $(OBJS)

%.so: %.c %.h
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) -f $(OBJS)

.PHONY: clean all
