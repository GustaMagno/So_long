/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:33:58 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/19 21:16:50 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int close_x(t_game *mlx)
{
	free_game(mlx);
	exit (0);
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
		return (write(1, "LESS ARGS", 10), 0);
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
	mlx.player.player_x *= 64;
	mlx.player.player_y *= 64;
	load_images(&mlx);
	mlx_loop_hook(mlx.mlx, update_game, &mlx);
	return (mlx_loop(mlx.mlx));
}
