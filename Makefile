NAME = main
CC = cc
CFLAGS = -Werror -Wall -Wextra -I$(FT_PRINTF_DIR) -I$(LIBFT_DIR)

LIBFT_DIR = 0_libft
LIBFT = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = 1_ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(FT_PRINTF) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(FT_PRINTF_DIR) fclean

norm:
	norminette $(LIBFT_DIR) $(FT_PRINTF_DIR)


.PHONY: all clean fclean re $(LIBFT) $(FT_PRINTF)
