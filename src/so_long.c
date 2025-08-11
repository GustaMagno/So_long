/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:33:58 by gustoliv          #+#    #+#             */
/*   Updated: 2025/07/26 15:52:14 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_game(t_game *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	mlx_destroy_image(data->mlx, data->img);
	free(data->mlx);
	free(data->img);
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
void	update_player_position(t_player *player)
{
	if  (player->keyboard[XK_W] || player->keyboard[XK_w])
		player->y -= 4;
	if  (player->keyboard[XK_S] || player->keyboard[XK_s])
		player->y += 4;
	if  (player->keyboard[XK_A] || player->keyboard[XK_a])
		player->x -= 4;
	if  (player->keyboard[XK_D] || player->keyboard[XK_d])
		player->x += 4;
}

int	update_game(t_game *mlx)
{
	update_player_position(&mlx->player);
	printf("x: %i y: %i\n", mlx->player.x, mlx->player.y);
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, mlx->player.x, mlx->player.y);
	usleep(10000);	
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
	static t_game 	mlx;
	static t_player p = {.w = 64, .h = 64};
	static	t_map 	map;

	if (argc != 2)
		return (1);
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, 800, 600, "So_Long");
	mlx_hook(mlx.mlx_win, 2,  1L << 0, key_press, &mlx);
	mlx_hook(mlx.mlx_win, 3,  1L << 1, key_release, &mlx);
	build_map(argv[1], mlx, map)
	mlx_hook(mlx.mlx_win, 17, 0, close_x, &mlx);
	mlx_do_sync(mlx.mlx);
	mlx_loop_hook(mlx.mlx, update_game, &mlx);
	mlx.mlx_win = mlx_new_window(mlx.mlx, map.len_row * 32, map.len_colunm * 32 , "So_Long");
	mlx.img = mlx_xpm_file_to_image(mlx.mlx, "redslime.xpm", &p.w, &p.h);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, p.x, p.y);
	return (mlx_loop(mlx.mlx));
}
