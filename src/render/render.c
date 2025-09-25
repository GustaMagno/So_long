/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:32:11 by gustoliv          #+#    #+#             */
/*   Updated: 2025/09/01 20:32:11 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_img	load_img(t_game *mlx, char *path)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(mlx->mlx, path, &img.w, &img.h);
	if (!img.img)
		return (img);
	img.frame = 0;
	img.invert = 0;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	return (img);
}

void	load_images(t_game *mlx)
{
	mlx->images.player = load_img(mlx, "images/slime.xpm");
	mlx->images.player.h = 64;
	mlx->images.player.w = 64;
	mlx->images.coin = load_img(mlx, "images/coin.xpm");
	mlx->images.coin.h = 64;
	mlx->images.coin.w = 64;
	mlx->images.wall = load_img(mlx, "images/wall.xpm");
	mlx->images.exit = load_img(mlx, "images/exit.xpm");
	mlx->images.ground = load_img(mlx, "images/ground.xpm");
	if ((!mlx->images.player.img) || (!mlx->images.coin.img)
		|| (!mlx->images.wall.img) || (!mlx->images.exit.img)
		|| (!mlx->images.ground.img))
		free_game(mlx);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (color == 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

static int	my_mlx_pixel_get(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	return (*(unsigned int *)dst);
}

void	put_img(t_game *mlx, t_img *img, int x, int y)
{
	int	sy;
	int	sx;
	int	color;

	sy = 0;
	while (sy < img->h)
	{
		sx = 0;
		while (sx < img->w)
		{
			if (img->invert)
				color = my_mlx_pixel_get(img, (64 - sx + (img->frame * 64)),
						sy);
			else
				color = my_mlx_pixel_get(img, sx + (img->frame * 64), sy);
			my_mlx_pixel_put(&mlx->buffer, x + sx, y + sy, color);
			sx++;
		}
		sy++;
	}
}
