#ifndef SO_LONG_H
# define SO_LONG_H
#  include <limits.h>
#  include <stdarg.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <unistd.h>
#  include "../minilibx-linux/mlx.h"
#  include <sys/time.h>
#  include <X11/keysym.h>


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

typedef struct s_map
{
	char	**map;
	int		fd;
	char	*str;
	int		i;
	int		len_row;
	int		len_colunm;
}t_map;


int		key_press(int key, t_game *mlx);
int		close_x(t_game *mlx);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size)

#endif