NAME	= so_long
CC		= cc
CFLAGS	= -g -O3 -Iinclude

MLX_DIR	= ./minilibx-linux
MLX_LIB	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS	= $(shell find ./src -name "*.c")
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
	
re: fclean all

r:
	make re && clear && ./$(NAME)

.PHONY: all clean fclean re run