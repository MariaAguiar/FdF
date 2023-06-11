/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:19 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/06 14:52:18 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	recolor(int zi, int rf, int gf, int bf)
{
	int	r;
	int	g;
	int	b;
	int	j;

	r = (zi >> 16) & 0xFF;
	g = (zi >> 8) & 0xFF;
	b = (zi) & 0xFF;
	j = 2;
	if (r < rf)
		r += j;
	else if (r > rf)
		r -= j;
	if (g < gf)
		g += j;
	else if (g > gf)
		g -= j;
	if (b < bf)
		b += j;
	else if (b > bf)
		b -= j;
	return ((zi << 24) | r << 16 | g << 8 | b);
}

void	colorize(t_matrix *matrix)
{
	int	max;
	int	min;
	int	x;
	int	y;

	max = max_z(matrix->tot_rows, matrix->tot_cols, matrix->mat);
	min = min_z(matrix->tot_rows, matrix->tot_cols, matrix->mat);
	x = -1;
	while (++x < matrix->tot_rows)
	{
		y = -1;
		while (++y < matrix->tot_cols)
		{
			if (matrix->mat[x][y] <= (max - min) / 8)
				matrix->mat[x][y] = 0x0005F2AF;
			else if (matrix->mat[x][y] > ((max - min) / 8) && \
			matrix->mat[x][y] <= ((max - min) / 8) * 4)
				matrix->mat[x][y] = 0x0049BF9E;
			else if (matrix->mat[x][y] > ((max - min) / 8) * 4 && \
			matrix->mat[x][y] <= ((max - min) / 8) * 7)
				matrix->mat[x][y] = 0x00F2CA80;
			else
				matrix->mat[x][y] = 0x00F29191;
		}
	}
}

void	draw_midlines(t_data *img, t_matrix *mat, double **bx, double **by)
{
	int			x;
	int			y;
	t_vector	*vec;

	vec = malloc(sizeof(*vec));
	if (!vec)
		return ;
	x = 0;
	while (++x < mat->tot_rows)
	{
		y = 1;
		while (y < mat->tot_cols)
		{
			begin_coord(vec, bx[x - 1][y - 1], by[x - 1][y - 1]);
			end_coord(vec, bx[x][y - 1], by[x][y - 1]);
			draw_line(img, vec, mat->mat[x - 1][y - 1], mat->mat[x][y - 1]);
			end_coord(vec, bx[x - 1][y], by[x - 1][y]);
			draw_line(img, vec, mat->mat[x - 1][y - 1], mat->mat[x - 1][y]);
			y++;
		}
	}
	free(vec);
}

void	draw_hedges(t_data *img, t_matrix *mat, double **bx, double **by)
{
	int			x;
	int			y;
	t_vector	*vec;

	vec = malloc(sizeof(*vec));
	if (!vec)
		return ;
	x = mat->tot_rows - 1;
	y = 1;
	while (y < mat->tot_cols)
	{
		begin_coord(vec, bx[x][y - 1], by[x][y - 1]);
		end_coord(vec, bx[x][y], by[x][y]);
		draw_line(img, vec, mat->mat[x][y - 1], mat->mat[x][y]);
		y++;
	}
	free(vec);
}

void	draw_vedges(t_data *img, t_matrix *mat, double **bx, double **by)
{
	int			x;
	int			y;
	t_vector	*vec;

	vec = malloc(sizeof(*vec));
	if (!vec)
		return ;
	x = 0;
	while (++x < mat->tot_rows)
	{
		y = 1;
		while (y < mat->tot_cols)
		{
			y++;
			if (y == mat->tot_cols)
			{
				begin_coord(vec, bx[x - 1][y - 1], by[x - 1][y - 1]);
				end_coord(vec, bx[x][y - 1], by[x][y - 1]);
				draw_line(img, vec, mat->mat[x - 1][y - 1], mat->mat[x][y - 1]);
				break ;
			}
		}
	}
	free(vec);
}
