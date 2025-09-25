/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:41:19 by gustoliv          #+#    #+#             */
/*   Updated: 2025/09/01 20:41:19 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"

void	tales_conditions(t_game *mlx, char c, int x, int y)
{
	if (c == OB_0 || c == OB_P || c == OB_C || c == '0')
		put_img(mlx, &mlx->images.ground, x * 64, y * 64);
	if (c == OB_C)
		put_img(mlx, &mlx->images.coin, x * 64, y * 64);
	if (c == OB_E)
		put_img(mlx, &mlx->images.exit, x * 64, y * 64);
	if (c == '1')
		put_img(mlx, &mlx->images.wall, x * 64, y * 64);
}

void	put_map(t_game *mlx, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			tales_conditions(mlx, map[i][j], j, i);
			j++;
		}
		i++;
	}
}

int	build_map(char *ber, t_game *mlx)
{
	char	*strtemp;
	int		fd;

	fd = open(ber, O_RDONLY);
	if (!parsing_ber(fd, ber))
		return (write(2, "Error\n", 7), 0);
	while (1)
	{
		strtemp = get_next_line(fd);
		if (strtemp && strtemp[0] == '\n' && strtemp[1] == '\0')
			return (close(fd), write(2, "Error\n", 7), 0);
		if (!strtemp)
			break ;
		mlx->map.str = ft_strjoin2(mlx->map.str, strtemp);
		free(strtemp);
	}
	close(fd);
	mlx->map.map = ft_split(mlx->map.str, '\n');
	if (!(mlx->map.map) || !check_map(mlx->map.map, mlx))
		return (write(2, "Error\n", 7), 0);
	flood_fill(mlx->map.map, mlx->player.player_x, mlx->player.player_y);
	if (!(check_flood(mlx->map.map)))
		return (write(2, "Error\n", 7), 0);
	return (1);
}
