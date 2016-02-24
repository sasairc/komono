TARGET	= ysh
CMDLINE	:= 0

SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)

all: $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
ifeq ($(CMDLINE), 0)
	@echo "  BUILD   $@"
	@$(CC) $(LDFLAGS) $^ -o $@
else
	$(CC) $(LDFLAGS) $^ -o $@
endif

%.o: %.c %.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      $@"
	@$(CC) $(DEFCFLAGS) $(CFLAGS) -c $< -o $@
else
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c $< -o $@
endif

clean:
	-$(RM) -f $(OBJS)
	-$(RM) -f $(TARGET)

.PHONY: all clean
