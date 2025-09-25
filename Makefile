NAME	= so_long
CC		= cc
CFLAGS	= -Iinclude -Wall -Wextra -Werror
OBJS_DIR = obj
MLX_DIR	= ./minilibx-linux
MLX_LIB	= $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS = ./src/libftfunc/ft_split.c \
       ./src//libftfunc/ft_strlcpy.c \
       ./src//libftfunc/ft_strjoinl.c \
       ./src//libftfunc/ft_strncmp.c \
       ./src//libftfunc/ft_strrchr.c \
       ./src/get_next_line.c \
       ./src/get_next_line_utils.c \
       ./src/map.c \
       ./src/parsing.c \
       ./src/render/render.c \
       ./src/so_long.c \
       ./src/update_game.c \
       ./src/colisions.c \
       ./src/flood_fill.c \
       ./src/free_game.c
OBJS	= $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(MLX_DIR) clean
	
fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(MLX_DIR) clean
	
re: fclean all

.PHONY: all clean fclean re