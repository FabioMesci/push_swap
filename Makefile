NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes
RM = rm -f

SRCS = srcs/main.c \
		srcs/parsing/flags.c \
		srcs/parsing/parsing.c \
		srcs/stack/stack.c \
		srcs/stack/stack_utils.c \
		srcs/utils/utils.c \
		srcs/utils/ft_split.c \
		srcs/ops/ops_utils.c \
		srcs/ops/ops_swap.c \
		srcs/ops/ops_push.c \
		srcs/ops/ops_rotate.c \
		srcs/ops/ops_rrotate.c \
		srcs/analysis/bench.c \
		srcs/analysis/disorder.c \
		srcs/analysis/index.c \
		srcs/sort/dispatch.c \
		srcs/sort/sort_adaptive.c \
		srcs/sort/sort_complex.c \
		srcs/sort/sort_medium.c \
		srcs/sort/sort_simple.c \
		srcs/sort/sort_small.c
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
