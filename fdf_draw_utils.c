/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:17:37 by margarida         #+#    #+#             */
/*   Updated: 2023/06/06 15:09:25 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	begin_coord(t_vector *vector, int x, int y)
{
	vector->xi = x;
	vector->yi = y;
}

void	end_coord(t_vector *vector, int x, int y)
{
	vector->xf = x;
	vector->yf = y;
}

int	min_z(int rows, int cols, double **blockz)
{
	int		min;
	int		x;
	int		y;

	y = 0;
	min = WHEI;
	while (y < rows)
	{
		x = -1;
		while (++x < cols)
		{
			if (blockz[y][x] < min)
				min = blockz[y][x];
		}
		y++;
	}
	return (min);
}

int	max_z(int rows, int cols, double **blockz)
{
	int		max;
	int		x;
	int		y;

	max = -WHEI;
	y = 0;
	while (y < rows)
	{
		x = -1;
		while (++x < cols)
		{
			if (blockz[y][x] > max)
				max = blockz[y][x];
		}
		y++;
	}
	return (max);
}

void	corr_blockz(int tab, int rows, int cols, double **blockz)
{
	int		x;
	int		y;
	int		range;
	int		min;

	y = -1;
	min = min_z(rows, cols, blockz);
	range = max_z(rows, cols, blockz) - min_z(rows, cols, blockz);
	while (++y < rows)
	{
		x = -1;
		while (++x < cols)
		{
			if (range)
				blockz[y][x] = (blockz[y][x] - min) / range;
			if (tab > WHEI * 0.035)
				blockz[y][x] *= tab;
			else
				blockz[y][x] *= WHEI * 0.075;
		}
	}
}
