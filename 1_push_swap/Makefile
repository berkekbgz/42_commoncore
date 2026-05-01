NAME		= push_swap
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Ift_printf -Ilibft

SRCS		= main.c \
			init.c \
			data_init.c \
			data_free.c \
			benchmark.c \
			ops_push.c \
			ops_rotate.c \
			ops_reverse_rotate.c \
			ops_swap.c \
			sort_simple.c \
			sort_medium.c \
			sort_complex.c \
			sort_adaptive.c \
			utils.c
OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR	= ft_printf
FT_PRINTF	= $(FT_PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FT_PRINTF) $(LIBFT)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(FT_PRINTF_DIR) fclean

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re
