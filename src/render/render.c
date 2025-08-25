/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 23:08:42 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/19 20:57:45 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


static t_img	load_img(t_game *mlx, char *path)
{
	t_img img;
	
	img.img = mlx_xpm_file_to_image(mlx->mlx, path, &img.w, &img.h);
	if (!img.img)
		return (img);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	return (img);
}

void	load_images(t_game *mlx)
{
	mlx->images.player[0] = load_img(mlx, "images/slime0.xpm");
	mlx->images.player[1] = load_img(mlx, "images/slime1.xpm");
	mlx->images.player[2] = load_img(mlx, "images/slime2.xpm");
	mlx->images.player[3] = load_img(mlx, "images/slime3.xpm");
	mlx->images.player[4] = load_img(mlx, "images/slime4.xpm");
	mlx->images.player[5] = load_img(mlx, "images/slime5.xpm");
	mlx->images.player[6] = load_img(mlx, "images/slime6.xpm");
	mlx->images.player[7] = load_img(mlx, "images/slime7.xpm");
	mlx->images.player[8] = load_img(mlx, "images/slime8.xpm");
	mlx->images.coin = load_img(mlx, "images/coin.xpm");
	mlx->images.wall = load_img(mlx, "images/wall.xpm");
	mlx->images.exit = load_img(mlx, "images/exit.xpm");
	mlx->images.ground = load_img(mlx, "images/ground.xpm");
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (color == 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static int	my_mlx_pixel_get(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void put_img(t_game *mlx, t_img *img, int x, int y)
{
	int sx;
	int sy;

	sy = 0;
	while (sy < img->h)
	{
		sx = 0;
		while (sx < img->w)
		{
			my_mlx_pixel_put(&mlx->buffer, x + sx, y + sy, 
			my_mlx_pixel_get(img, sx, sy));
			sx++;
		}
		sy++;
	}
}