/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:30:22 by marvin            #+#    #+#             */
/*   Updated: 2025/08/02 14:30:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

//colocar as condições do mapa como 1 0 E C P.
void	conditions_map(t_map tile, int row, int column, t_game mlx);
{
	static int p_position_x = 0;
	static int p_position_y = 0;

	if (tile->map[row][column] == 'P')
	{
		p_position_x = row;
		p_position_y = column;
	}

	else
		mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, p.x, p.y);
}

void	put_map(t_map map, t_game mlx)
{
	int row;
	int column;

	row = 0;
	column = 0;
	while (map.map[row])
	{
		while (map.map[row][column])
			conditions_map(map, row, column++, mlx);
		row++;
	}
}

int	input_verification(t_map map, int *row)
{
	static int	i = 0;
	static int	len_line = 0;
	static int	column = 0;
	static int	player_check = 0;

	i += (map->str[i] == '\n')
	while (map->str[i])
	{
		if (map->str[i] != '1' && map->str[i] != 'C' && map->str[i] != '0' && map->str[i] != 'P' && map->str[i] != 'E')
			return (free(map->str), 1);
		if (map->str[i] == 'P')
			player_check = 1;
		if (map->str[i] == 'P' && player_check)
			return (free(map->str), 1);
		i++;
	}
	column++;
	if (!len_line)
		len_line = i;
	if ((i / len_line) != column)
		return (free(map->str), 1);
	*row = i;
	return (0);
}
int	build_map(char *ber, t_game mlx, t_map *map)
{
	char	*strtemp;

	map->fd = open(ber, O_RDONLY);
	while (strtemp = get_next_line(map->fd))
	{
		map->str = ft_strjoin(map->str, strtemp, map->str);
		if (input_verification(map, &map->len_row))
			exit(0);
		map->len_colunm++;
	}
	mlx->mlx_win = mlx_new_window(mlx->mlx, map->len_row * 32, , "So_Long");
	map->map = ft_split(map.str, '\n');
	put_map(map, mlx);
}