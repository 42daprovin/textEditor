NAME = textEditor

DIR_S = src
DIR_O = objs

SOURCES = main.c \
					rawMode.c \
					error.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I inc

all: $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p $(DIR_O)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(INCLUDES) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS)/*.o
	rm -rf $(DIR_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all
