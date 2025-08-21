/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:25:18 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/13 20:27:53 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	print_map(char **map)
// {
// 	int i = 0;

// 	printf("\n");
// 	while (map[i])
// 	{
// 		printf("%s\n", map[i]);
// 		i++;	
// 	}
// 	printf("\n");
// }

int	check_flood(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P' || map[i][j] == 'C' || map[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] != 'P' && map[y][x] != 'C' && map[y][x] != 'E' && map[y][x] != '0')
		return ;
	map[y][x] += 5;
	flood_fill(map, x, y - 1);
	flood_fill(map, x + 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x - 1, y);
}
