NAME = ../../.bin/list
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRC = main.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lm -lreadline

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
