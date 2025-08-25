/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:11:29 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/19 21:11:43 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	update_player_position(t_game *mlx, char *keyboard)
{
	player_in_wall(mlx, keyboard[XK_d]  - keyboard[XK_a], keyboard[XK_s] - keyboard[XK_w], mlx->map.map);
	//put_img(mlx, &mlx->images.player, mlx->player.player_x, mlx->player.player_y);
}

int	update_game(t_game *mlx)
{	
	put_map(mlx, mlx->map.map);
	update_player_position(mlx, mlx->player.keyboard);
	
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->buffer.img, 0, 0);
	usleep(10000);
	return (0);	
}