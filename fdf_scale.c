/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 06:37:38 by margarida         #+#    #+#             */
/*   Updated: 2023/06/06 11:38:45 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	bignum(int first, int second)
{
	if (first > second)
		return (second);
	return (first);
}

void	corr_b(int rows, int cols, double corr, double **block)
{
	int	x;
	int	y;

	y = 0;
	while (y < rows)
	{
		x = -1;
		while (++x < cols)
			block[y][x] *= corr;
		y++;
	}
}

void	rescale(t_matrix *mat, double **bx, double **by)
{
	int		min;
	int		max;
	double	dif;
	double	corr;

	min = smlnum(min_z(mat->tot_rows, mat->tot_cols, bx), \
	min_z(mat->tot_rows, mat->tot_cols, by));
	max = smlnum(max_z(mat->tot_rows, mat->tot_cols, bx), \
	max_z(mat->tot_rows, mat->tot_cols, by));
	max = WHEI - max;
	dif = smlnum(min, max);
	corr = 1 / (1 - (20 / dif));
	corr_b(mat->tot_rows, mat->tot_cols, corr, bx);
	corr_b(mat->tot_rows, mat->tot_cols, corr, by);
	corr_blockx(mat->tot_rows, mat->tot_cols, bx);
	corr_blocky(mat->tot_rows - 1, mat->tot_cols, by);
}
