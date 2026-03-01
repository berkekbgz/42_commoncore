NAME = main
CC = cc
CFLAGS = -Werror -Wall -Wextra -I$(FT_PRINTF_DIR) -I$(LIBFT_DIR) -I$(GET_NEXT_LINE_DIR)

LIBFT_DIR = 0_libft
LIBFT = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = 1_ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

GET_NEXT_LINE_DIR = 1_get_next_line
GNL_SRC = $(GET_NEXT_LINE_DIR)/get_next_line.c $(GET_NEXT_LINE_DIR)/get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)

SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(GNL_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(GNL_OBJ) $(FT_PRINTF) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

clean:
	rm -f $(OBJ) $(GNL_OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(FT_PRINTF_DIR) fclean

norm:
	norminette $(LIBFT_DIR) $(FT_PRINTF_DIR) $(GET_NEXT_LINE_DIR)


.PHONY: all clean fclean re $(LIBFT) $(FT_PRINTF)
