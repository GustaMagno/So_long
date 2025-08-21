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

void	take_coin(t_game *mlx, char **map)
{
	int px;
	int py;
	
	px = (mlx->player.player_x);
	py = (mlx->player.player_y);
	if ((map[py / 64][px / 64] == OB_C && map[py / 64][(px + 63) / 64] == OB_C) )
		map[py / 64][px / 64] = OB_0;
	else if (map[(py + 63) / 64][px / 64] == OB_C && map[(py + 63) / 64][(px + 63) / 64] == OB_C)
		map[(py + 63) / 64][px / 64] = OB_C;
	if (map[py / 64][px / 64] == OB_C && map[(py + 63) / 64][px / 64] == OB_C)
		map[py / 64][px / 64] = OB_C;
	else if (map[py / 64][(px + 63) / 64] == OB_C && map[(py + 63) / 64][(px + 63) / 64] == OB_C)
		map[py / 64][(px + 63) / 64] = OB_C;
}

int	player_in_wall(t_game *mlx, int x, int y, char **map)
{
	int px;
	int py;
	

	px = (mlx->player.player_x) + x;
	py = (mlx->player.player_y) + y;

	printf("x : %i, y : %i - px: %i py: %i\n", x, y, px / 64, py / 64);
	if (y == -1 && (map[py / 64][px / 64] != '1' && map[py / 64][(px + 63) / 64] != '1') )
			mlx->player.player_y += y;
	else if (y == 1 && map[(py + 63) / 64][px / 64] != '1' && map[(py + 63) / 64][(px + 63) / 64] != '1')
		mlx->player.player_y += y;
	if (x == -1 && map[py / 64][px / 64] != '1' && map[(py + 63) / 64][px / 64] != '1')
			mlx->player.player_x += x;
	else if (x == 1 && map[py / 64][(px + 63) / 64] != '1' && map[(py + 63) / 64][(px + 63) / 64] != '1')
		mlx->player.player_x += x;
	take_coin(mlx, map);
	put_img(mlx, &mlx->images.player, mlx->player.player_x, mlx->player.player_y);
}