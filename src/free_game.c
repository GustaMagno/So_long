/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:39:06 by gustoliv          #+#    #+#             */
/*   Updated: 2025/09/01 20:39:06 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_images(t_game *mlx)
{
	if (mlx->images.player.img)
		mlx_destroy_image(mlx->mlx, mlx->images.player.img);
	if (mlx->images.coin.img)
		mlx_destroy_image(mlx->mlx, mlx->images.coin.img);
	if (mlx->images.exit.img)
		mlx_destroy_image(mlx->mlx, mlx->images.exit.img);
	if (mlx->images.wall.img)
		mlx_destroy_image(mlx->mlx, mlx->images.wall.img);
	if (mlx->images.ground.img)
		mlx_destroy_image(mlx->mlx, mlx->images.ground.img);
	if (mlx->buffer.img)
		mlx_destroy_image(mlx->mlx, mlx->buffer.img);
}

void	free_map(char **map)
{
	int	i;

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
		free_images(mlx);
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free_map(mlx->map.map);
	free(mlx->map.str);
	exit(0);
}
