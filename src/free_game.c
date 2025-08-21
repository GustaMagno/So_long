/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:12:23 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/19 21:12:33 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		mlx_destroy_image(mlx->mlx, mlx->buffer.img);
		free(mlx->buffer.img);
		free(mlx->buffer.addr);
	}
	free_map(mlx->map.map);
	free(mlx->map.str);
	exit(0);
}