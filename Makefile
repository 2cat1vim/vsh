.DEFAULT_GOAL := all

STROS = Windows
OS := $(shell uname)
ifeq ($(OS), Darwin)
	STROS := darwin
endif 
ifeq ($(OS), Linux)
	STROS := linux
else
	STROS := unknown
endif

NAME = vsh
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRC = srcs/main.c \
      srcs/opt.c \
	  srcs/env.c \
      srcs/readline.c \
      srcs/design.c

check_os:
	@if [ "$(STROS)" = "unknown" ]; then \
		echo 'Unsuported OS Detected: "$(STROS)"'; exit 1; \
	else \
		echo "Detected OS: $(STROS)";\
	fi

NAME := vsh_$(STROS)

OBJS = $(SRC:.c=.o)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lm -lreadline

all: check_os $(NAME)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all check_os clean fclean re
