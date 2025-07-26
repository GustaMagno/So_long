#ifndef SO_LONG_H
# define SO_LONG_H
#  include <limits.h>
#  include <stdarg.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <unistd.h>
#  include "../minilibx-linux/mlx.h"
#  include <X11/keysym.h>
#  include <sys/time.h>

#  define W 800
#  define H 600

typedef struct s_player
{
	int 	w;
	int 	h;
	int 	x;
	int 	y;
	char	keyboard[70000];
}t_player;
typedef struct s_game
{
	t_player	player;
	void		*mlx;
	void		*mlx_win;
	void		*img;
}t_game;


int	key_press(int key, t_game *mlx);
int close_x(t_game *mlx);

#endif