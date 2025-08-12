/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:11:16 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/12 20:30:13 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"


int	build_map(char *ber, t_game *mlx)
{
	char	*strtemp;
	int		fd;
	
	fd = open(ber, O_RDONLY);
	if (!parsing_ber(fd, ber))
		return (write(1, "MAPA INVALIDO", 13), 0);
	while (1)
	{
		strtemp = get_next_line(fd);
		if (strtemp && strtemp[0] == '\n' && strtemp[1] == '\0')
			return (write(1, "MAPA INVALIDO", 13), 0);
		if (!strtemp)
			break ;
		mlx->map.str = ft_strjoin2(mlx->map.str, strtemp);
	}
	mlx->map.map = ft_split(mlx->map.str, '\n');
	if (!check_map(mlx->map.map, mlx))
		return (write(1, "MAPA INVALIDO", 13), 0);
	close(fd);
	flood_fill(mlx->map.map, mlx->player.player_x, mlx->player.player_y);
	print_map(mlx->map.map);
	exit(0);
	return (1);
}
