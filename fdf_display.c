/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:15:22 by margarida         #+#    #+#             */
/*   Updated: 2023/06/06 07:13:34 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	quits(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window (img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	destroy_matrix(&img->matrix);
	exit(EXIT_SUCCESS);
}

int	read_keys(int key_pressed, void *param)
{
	t_data	*img;

	img = (t_data *) param;
	if (key_pressed == ESC)
		quits(img);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < WWID && y < WHEI)
	{
		dst = data->addr + (y * data->line_length + \
		x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_data *data, t_vector *vector, int zi, int zf)
{
	double	dx;
	double	dy;
	double	pxx;
	double	pxy;
	int		pxs;

	pxx = vector->xi;
	pxy = vector->yi;
	dx = vector->xf - vector->xi;
	dy = vector->yf - vector->yi;
	pxs = sqrt((dx * dx) + (dy * dy));
	dx /= pxs;
	dy /= pxs;
	pxx = vector->xi;
	pxy = vector->yi;
	while (pxs)
	{
		my_mlx_pixel_put(data, pxx, pxy, zi);
		zi = recolor(zi, ((zf >> 16) & 0xFF), \
		((zf >> 8) & 0xFF), ((zf) & 0xFF));
		pxx += dx;
		pxy += dy;
		--pxs;
	}
}

void	display_in_canvas(t_matrix *matrix)
{
	t_data	img;
	double	**blockx;
	double	**blocky;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, WWID, WHEI, "FdF");
	img.img = mlx_new_image(img.mlx, WWID, WHEI);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	img.matrix = matrix;
	blockx = creat_blockx(matrix, -1, -1);
	blocky = creat_blocky(matrix, -1, -1);
	rescale(matrix, blockx, blocky);
	colorize(matrix);
	draw_midlines(&img, matrix, blockx, blocky);
	draw_hedges(&img, matrix, blockx, blocky);
	draw_vedges(&img, matrix, blockx, blocky);
	free_blocks(matrix->tot_rows, blockx, blocky);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_key_hook (img.mlx_win, read_keys, &img);
	mlx_hook(img.mlx_win, 17, (1L << 0), quits, &img);
	mlx_loop(img.mlx);
}
