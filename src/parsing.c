/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:55:41 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/12 19:34:55 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_rectangle(char **map, int *lenline, int *lencolumn)
{
	int i;
	int j;
	int save_line;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (i == 0)
			save_line = j;
		else if (save_line != j)
			return (0);
		i++;
	}
	if (i < 3)
		return (0);
	*lenline = save_line;
	*lencolumn = i;
	return (1);
}

int	check_wall(char **map)
{
	int check;
	int i;
	int j;
	int l_line;
	int lcol;

	i = 0;
	if (!check_rectangle(map, &l_line,  &lcol))
		return (0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 && map[i][j] != '1' ) || (i == lcol - 1 && map[i][j] != '1'))
				return (0);
			else if ((j == 0 || j == l_line - 1) && map[i][j] != '1')
				return (0);
			else
				j++;
		}
		i++;
	}
	return (1);
}

int conditions(char c, int final)
{
	static int check_P;
	static int check_C;
	static int check_E;

	if ((check_P && (c == 'P')) || (check_E && (c == 'E')))
		return (0);
	if (c == 'P')
		check_P = 1;
	else if (c == 'C')
		check_C = 1;
	else if (c == 'E')
		check_E = 1;
	else if (c != '0' && c != '1')
		return (0);
	if ((final && !check_C) || (final && !check_E) || (final && !check_P))
		return (0);
	return (1);
}

int check_map(char **map, t_game *mlx)
{
	int i;
	int j;
	int check;
	
	i = 0;
	check = check_wall(map);
	while (map[i])
	{	
		j = 0;
		while (check && map[i][j])
		{	
			if (map[i][j] == 'P')
			{
				mlx->player.player_x = j;
				mlx->player.player_y = i;
			}
			check = conditions(map[i][j++], 0);
		}
		if (!check)
			return (0);
		i++;
	}
	check = conditions('0', 1);
	return (check);
}

int parsing_ber(int fd, char *ber)
{
	char	*str;

	if (fd < 0)
		return (0);
	str = ft_strrchr(ber, '.');
	if (ft_strncmp(str, ".ber", 4) != 0)
		return (0);
	return (1);
}
