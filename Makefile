NAME = vsh
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRC = srcs/main.c \
      srcs/opt.c \
      srcs/readline.c

OBJS = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lm -lreadline

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
