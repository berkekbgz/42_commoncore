NAME        	= push_swap
CC          	= cc
CFLAGS      	= -Wall -Wextra -Werror -Iinclude -Ift_printf

SRCS        	= 	main.c \
					init.c \
					ops_push.c \
					ops_rotate.c \
					ops_reverse_rotate.c \
					ops_swap.c \
					sort_simple.c \
					sort_medium.c \
					utils.c \
					data_utils.c
OBJS        	= $(SRCS:.c=.o)

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft

FT_PRINTF_DIR	= ft_printf
FT_PRINTF		= $(FT_PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FT_PRINTF) $(LIBFT)

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
