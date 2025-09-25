/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:45:34 by gustoliv          #+#    #+#             */
/*   Updated: 2025/09/01 20:45:34 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*simple_putnumber(int number)
{
	char		c;
	static char	str[15];
	int			i;

	i = 13;
	c = str[i];
	str[i] = '0';
	while (number > 0)
	{
		str[i] = (number % 10) + 48;
		number /= 10;
		if (number > 0)
			i--;
	}
	if (c != str[13])
	{
		write(1, "STEPS: ", 8);
		write(1, &str[i], 14 - i);
		write(1, "\n", 1);
	}
	return (&str[i]);
}

void	update_player_position(t_game *mlx, char *keyboard)
{
	player_in_wall(mlx, keyboard[XK_d] - keyboard[XK_a], keyboard[XK_s]
		- keyboard[XK_w], mlx->map.map);
}

int	update_game(t_game *mlx)
{
	put_map(mlx, mlx->map.map);
	update_player_position(mlx, mlx->player.keyboard);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->buffer.img, 0, 0);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 10, 10, 0xFFFFFF, "STEPS:");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 50, 10, 0xFFFFFF,
		simple_putnumber(mlx->player.steps / 64));
	usleep(10000);
	return (0);
}
