/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:33:58 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/13 22:43:02 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;
	int	j;

	i = 0;
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
		mlx_destroy_image(mlx->mlx, mlx->images.player);
		mlx_destroy_image(mlx->mlx, mlx->images.coin);
		mlx_destroy_image(mlx->mlx, mlx->images.exit);
		mlx_destroy_image(mlx->mlx, mlx->images.wall);
		mlx_destroy_image(mlx->mlx, mlx->images.ground);
		free(mlx->map.map);
		mlx_destroy_window(mlx->mlx,mlx->mlx_win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
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
		player->player_y -= 4;
	if  (player->keyboard[XK_S] || player->keyboard[XK_s])
		player->player_y += 4;
	if  (player->keyboard[XK_A] || player->keyboard[XK_a])
		player->player_x -= 4;
	if  (player->keyboard[XK_D] || player->keyboard[XK_d])
		player->player_x += 4;
}

int	update_game(t_game *mlx)
{
	// if (nao passou 100ml)
	// 	return ;
	//update_time_diff(mlx); //funcao para dar update no tempo
	update_player_position(&mlx->player);
	printf("x: %i y: %i\n", mlx->player.player_x, mlx->player.player_y);
	put_map(mlx, mlx->map.map);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->images.player, mlx->player.player_x, mlx->player.player_y);
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

void	put_tiles(t_game *mlx, int w, int h)
{
	mlx->images.player = mlx_xpm_file_to_image(mlx->mlx, "redslime.xpm", &w, &h);
	mlx->images.coin = mlx_xpm_file_to_image(mlx->mlx, "coin.xpm", &w, &h);
	mlx->images.wall = mlx_xpm_file_to_image(mlx->mlx, "wall.xpm", &w, &h);
	mlx->images.exit = mlx_xpm_file_to_image(mlx->mlx, "exit.xpm", &w, &h);
	mlx->images.ground = mlx_xpm_file_to_image(mlx->mlx, "ground.xpm", &w, &h);
}

int main(int argc, char **argv)
{
	static t_game mlx;

	if (argc != 2)
		return (write(1, "POUCOS ARGS", 11), 0);
	if (!build_map(argv[1], &mlx))
		free_game(&mlx);
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.map.len_r  * 64, mlx.map.len_c * 64, "So_Long");
	mlx_hook(mlx.mlx_win, 2,  1L << 0, key_press, &mlx);
	mlx_hook(mlx.mlx_win, 3,  1L << 1, key_release, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, close_x, &mlx);
	mlx_do_sync(mlx.mlx);
	mlx.player.player_x *= 64;
	mlx.player.player_y *= 64;
	put_tiles(&mlx, 64, 64);
	mlx_loop_hook(mlx.mlx, update_game, &mlx);
	put_map(&mlx, mlx.map.map);
	return (mlx_loop(mlx.mlx));
}
