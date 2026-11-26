NAME = push_swap
CHECKER = checker
CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes
RM = rm -f

SRCS = srcs/parsing/flags.c \
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
		srcs/sort/sort_complex_move.c \
		srcs/sort/sort_medium.c \
		srcs/sort/sort_simple.c \
		srcs/sort/sort_small.c \
		srcs/sort/sort_utils.c
MAIN = srcs/main.c
BONUS_SRCS = bonus/checker_bonus.c \
		bonus/get_next_line_bonus.c \
		bonus/get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)
MAIN_OBJ = $(MAIN:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) -o $(NAME)

bonus: $(CHECKER)

$(CHECKER): $(OBJS) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(BONUS_OBJS) -o $(CHECKER)

%.o: %.c includes/push_swap.h includes/header_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN_OBJ) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(CHECKER)

re: fclean all

.PHONY: clean fclean re all bonus
