/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:33:58 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/18 19:45:09 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_in_wall(t_game *mlx, int x, int y)
{
	px_left = x / 64;
	// printf("TALE : %c\n", mlx->map.map[y / 64][x / 64]);
	if (mlx->map.map[y / 64][x / 64] == '1')
		return (0);
	if (mlx->map.map[(y / 64) + 1][x / 64] == '1' || mlx->map.map[y / 64][(x / 64) + 1] == '1')
		return (0);
	return (1);
}

int	player_position(t_game *mlx, char p_walk)
{
	if (p_walk == 'W')
		return (player_in_wall(mlx, mlx->player.player_x, mlx->player.player_y - 4));
	if (p_walk == 'S')
		return (player_in_wall(mlx, mlx->player.player_x, mlx->player.player_y + 4));
	if (p_walk == 'A')
		return (player_in_wall(mlx, mlx->player.player_x - 4, mlx->player.player_y));
	if (p_walk == 'D')
		return (player_in_wall(mlx, mlx->player.player_x + 4, mlx->player.player_y));
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
		mlx_destroy_image(mlx->mlx, mlx->images.player);
		mlx_destroy_image(mlx->mlx, mlx->images.coin);
		mlx_destroy_image(mlx->mlx, mlx->images.exit);
		mlx_destroy_image(mlx->mlx, mlx->images.wall);
		mlx_destroy_image(mlx->mlx, mlx->images.ground);
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
void	update_player_position(t_game *mlx)
{
	// printf("TALE : %c\n", mlx->map.map[mlx->player.player_y / 64][mlx->player.player_x / 64]);
	if  (mlx->player.keyboard[XK_W] || mlx->player.keyboard[XK_w] && player_position(mlx, 'W'))
		mlx->player.player_y -= 4;
	if  (mlx->player.keyboard[XK_S] || mlx->player.keyboard[XK_s] && player_position(mlx, 'S'))
		mlx->player.player_y += 4;
	if  (mlx->player.keyboard[XK_A] || mlx->player.keyboard[XK_a] && player_position(mlx, 'A'))
		mlx->player.player_x -= 4;
	if  (mlx->player.keyboard[XK_D] || mlx->player.keyboard[XK_d] && player_position(mlx, 'D'))
		mlx->player.player_x += 4;
}

int	update_game(t_game *mlx)
{
	// if (nao passou 100ml)
	// 	return ;
	//update_time_diff(mlx); //funcao para dar update no tempo
	update_player_position(mlx);
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
