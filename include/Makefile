#
# 簡易Makefile
#

PREFIX	:= /usr/local
MAKE	:= make
CC	:= cc
rm	:= rm
CFLAGS	=
SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.so)
PKGCFG	= `pkg-config --cflags --libs glib-2.0`

DEFCFLAGS = -shared -fPIC \
	$(PKGCFG)

all: $(OBJS)

%.so: %.c
	$(CC) $(DEFCFLAGS) $(CFLAGS) $< -o libsasairc_$@

clean:
	-$(RM) -f *.so

install: $(OBJS)
	install -pd $(PREFIX)/lib
	install -pd $(PREFIX)/include/sasairc
	install -pm 755 *.so $(PREFIX)/lib
	install -pm 644 *.h $(PREFIX)/include/sasairc

.PHONY:	all	\
	install	\
	clean
