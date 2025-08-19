/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colisions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:17:02 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/19 21:20:22 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_in_wall(t_game *mlx, int x, int y, char **map)
{
	int px;
	int py;
	

	px = (mlx->player.player_x) + x;
	py = (mlx->player.player_y) + y;

	printf("x : %i, y : %i - px: %i py: %i c: %c\n", x, y, px / 64, py / 64, 'c');
	if (y == -1 && (map[py / 64][px / 64] != '1' && map[py / 64][(px + 63) / 64] != '1') )
			mlx->player.player_y += y;
	else if (y == 1 && map[(py + 63) / 64][px / 64] != '1' && map[(py + 63) / 64][(px + 63) / 64] != '1')
		mlx->player.player_y += y;
	if (x == -1 && map[py / 64][px / 64] != '1' && map[(py + 63) / 64][px / 64] != '1')
			mlx->player.player_x += x;
	else if (x == 1 && map[py / 64][(px + 63) / 64] != '1' && map[(py + 63) / 64][(px + 63) / 64] != '1')
		mlx->player.player_x += x;
	// else if (x == 1 && map[(py + 64) / 64][px / 64] != '1' && map[(py + 64) / 64][(px + 64) / 64] != '1')
	// 	mlx->player.player_x += x;
	put_img(mlx, &mlx->images.player, mlx->player.player_x, mlx->player.player_y);
	tes(mlx, px, py);
	tes(mlx, px, py + 64);
	tes(mlx, px + 64, py);
	tes(mlx, px + 64 , py + 64);
}