INCLUDE_DIRS := .
CPPFLAGS += $(addprefix -I ,$(INCLUDE_DIRS))
HEADERS := $(wildcard *.h)
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
TARGET := program

vpath %.h $(INCLUDE_DIRS)

.PHONY: all clean fclean re etags

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

etags:
	etags *.[ch]

clean:
	-rm -f $(OBJS)

fclean: clean
	-rm -f $(TARGET)

re: fclean all
