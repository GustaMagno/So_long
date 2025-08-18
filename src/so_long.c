/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:33:58 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/18 23:45:14 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_in_wall(t_game *mlx, int x, int y, char **map)
{
	int px;
	int py;

	px = ((int)mlx->player.player_x / 64) + x;
	py = ((int)mlx->player.player_y / 64 ) + y;

	printf("x : %i, y : %i - px: %i py: %i c: %c\n", x, y, px * 64, py * 64, map[py][px]);
	if (map[py][px] != '1')
	{
		mlx->player.player_x += x * 0.1f;
		mlx->player.player_y += y * 0.1f;
	}
	put_img(mlx, &mlx->images.player, (int)mlx->player.player_x * 64, (int)mlx->player.player_y * 64);
	my_mlx_pixel_put(&mlx->buffer, px * 64, py * 64, 0x4EC5F1);
}

int	player_position(t_game *mlx, char p_walk)
{
	if (p_walk == 'W')
		return (player_in_wall(mlx, mlx->player.player_x, mlx->player.player_y - 1, 'W'));
	if (p_walk == 'S')
		return (player_in_wall(mlx, mlx->player.player_x, mlx->player.player_y + 1, 'S'));
	if (p_walk == 'A')
		return (player_in_wall(mlx, mlx->player.player_x - 1, mlx->player.player_y, 'A'));
	if (p_walk == 'D')
		return (player_in_wall(mlx, mlx->player.player_x + 1, mlx->player.player_y, 'D'));
	return (1);
}

void	free_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_game(t_game *mlx)
{
	if (mlx->mlx)
	{
		mlx_destroy_image(mlx->mlx, mlx->images.player.img);
		mlx_destroy_image(mlx->mlx, mlx->images.coin.img);
		mlx_destroy_image(mlx->mlx, mlx->images.exit.img);
		mlx_destroy_image(mlx->mlx, mlx->images.wall.img);
		mlx_destroy_image(mlx->mlx, mlx->images.ground.img);
		mlx_destroy_window(mlx->mlx,mlx->mlx_win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free_map(mlx->map.map);
	free(mlx->map.str);
	exit(0);
}
int close_x(t_game *mlx)
{
	free_game(mlx);
	exit (0);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void	update_player_position(t_game *mlx, char *keyboard)
{
	player_in_wall(mlx, keyboard[XK_d]  - keyboard[XK_a], keyboard[XK_s] - keyboard[XK_w], mlx->map.map);
	// printf("TALE : %c\n", mlx->map.map[mlx->player.player_y / 64][mlx->player.player_x / 64]);
	// if  (mlx->player.keyboard[XK_W] || mlx->player.keyboard[XK_w] && player_position(mlx, 'W'))
	// 	mlx->player.player_y -= 1;
	// if  (mlx->player.keyboard[XK_S] || mlx->player.keyboard[XK_s] && player_position(mlx, 'S'))
	// 	mlx->player.player_y += 1;
	// if  (mlx->player.keyboard[XK_A] || mlx->player.keyboard[XK_a] && player_position(mlx, 'A'))
	// 	mlx->player.player_x -= 1;
	// if  (mlx->player.keyboard[XK_D] || mlx->player.keyboard[XK_d] && player_position(mlx, 'D'))
	// 	mlx->player.player_x += 1;
}

int	update_game(t_game *mlx)
{	
	put_map(mlx, mlx->map.map);
	update_player_position(mlx, mlx->player.keyboard);
	
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->buffer.img, 0, 0);
	usleep(10000);
	return (0);	
}

int	key_release(int key, t_game *mlx)
{
	mlx->player.keyboard[key] = 0;
	return (0);
}

int	key_press(int key, t_game *mlx)
{
	if (key == XK_Escape)
		free_game(mlx);
	mlx->player.keyboard[key] = 1;
	return (0);
}



int main(int argc, char **argv)
{
	static t_game mlx;

	if (argc != 2)
		return (write(1, "POUCOS ARGS", 11), 0);
	if (!build_map(argv[1], &mlx))
		free_game(&mlx);
	mlx.mlx = mlx_init();
	mlx.buffer.w = mlx.map.len_r  * 64;
	mlx.buffer.h = mlx.map.len_c * 64;
	mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.map.len_r  * 64, mlx.map.len_c * 64, "So_Long");
	mlx.buffer.img = mlx_new_image(mlx.mlx, mlx.map.len_r * 64, mlx.map.len_c * 64);
	mlx.buffer.addr = mlx_get_data_addr(mlx.buffer.img, &mlx.buffer.bits_per_pixel, &mlx.buffer.line_length,
								&mlx.buffer.endian);
	mlx_hook(mlx.mlx_win, 2,  1L << 0, key_press, &mlx);
	mlx_hook(mlx.mlx_win, 3,  1L << 1, key_release, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, close_x, &mlx);
	mlx_do_sync(mlx.mlx);
	load_images(&mlx);
	mlx_loop_hook(mlx.mlx, update_game, &mlx);
	return (mlx_loop(mlx.mlx));
}
