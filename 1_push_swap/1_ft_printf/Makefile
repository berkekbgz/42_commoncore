NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = ft_printf.c \
	  ft_put/ft_putcharstr.c \
	  ft_put/ft_putptr.c \
	  ft_put/ft_puthex.c \
	  ft_put/ft_putint.c

OBJ= $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
