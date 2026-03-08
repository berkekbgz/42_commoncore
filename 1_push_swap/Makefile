NAME        	= push_swap
CC          	= cc
CFLAGS      	= -Wall -Wextra -Werror -Iinclude -Ift_printf

SRCS        	= 	src/main.c \
					src/init.c \
					src/ops_push.c \
					src/ops_rotate.c \
					src/ops_reverse_rotate.c \
					src/ops_swap.c \
					src/sort_simple.c \
					src/utils.c
OBJS        	= $(SRCS:.c=.o)

FT_PRINTF_DIR	= ft_printf
FT_PRINTF		= $(FT_PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FT_PRINTF)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re $(LIBFT) $(FT_)
