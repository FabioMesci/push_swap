NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes
RM = rm -f

SRCS = srcs/main.c srcs/utils.c srcs/parsing.c srcs/stack.c \
		srcs/flags.c srcs/ops_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c includes/push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
