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
	char	keyboard[70000];
	int		player_x;
	int		player_y;
}t_player;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int 	w;
	int 	h;
	int		endian;
}				t_img;

typedef struct s_images
{
	t_img	ground;
	t_img	wall;
	t_img	player;
	t_img	exit;
	t_img	coin;
}t_images;
typedef struct s_map
{
	char	**map;
	char	*str;
	int		i;
	int		len_r;
	int		len_c;
}t_map;
typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_images	images;
	t_img		buffer;
	void		*mlx;
	void		*mlx_win;
}t_game;


typedef enum e_type {
	OB_P = 'P' + 5,
	OB_0 = '0' + 5,
	OB_E = 'E' + 5,
	OB_C = 'C' + 5
} t_type;

int				key_press(int key, t_game *mlx);
int 			close_x(t_game *mlx);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split(char const *s, char c);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				build_map(char *ber, t_game *mlx);
int 			parsing_ber(int fd, char *ber);
char			*ft_strjoin2(char *s1, const char *s2);
int 			parsing_ber(int fd, char *ber);
int 			check_map(char **map, t_game *mlx);
int 			conditions(char c, int final);
int				check_wall(char **map, t_game *mlx);
void 			flood_fill(char **map, int x, int y);
void 			print_map(char **map);
int				check_flood(char **map);
void			put_map(t_game *mlx, char **map);
void			load_images(t_game *mlx);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
void 			put_img(t_game *mlx, t_img *img, int x, int y);
int				update_game(t_game *mlx);
void			update_player_position(t_game *mlx, char *keyboard);
unsigned long	get_time(void);
void			free_game(t_game *mlx);
void			free_map(char **map);
int				player_in_wall(t_game *mlx, int x, int y, char **map)

#endif