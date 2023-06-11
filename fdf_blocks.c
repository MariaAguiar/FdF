/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_blocks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:51:25 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/06 15:15:33 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	smlnum(int rows, int cols)
{
	if (rows < cols)
		return (cols);
	return (rows);
}

void	corr_blocky(int rows, int cols, double **blocky)
{
	double	tab;
	int		mid;
	int		x;
	int		y;

	mid = ((blocky[rows][cols - 1] - blocky[0][0]) / 2);
	if (mid < 0)
		mid *= -1;
	mid += blocky[0][0];
	tab = (WHEI / 2) - mid;
	y = 0;
	while (y <= rows)
	{
		x = -1;
		while (++x < cols)
			blocky[y][x] += tab;
		y++;
	}
}

double	**creat_blocky(t_matrix *matrix, int y, int x)
{
	double	**blocky;
	int		sml;
	int		smltab;
	int		tmpy;
	int		tmpx;

	blocky = solo_matrix(matrix->tot_rows, matrix->tot_cols);
	if (!blocky)
		return (NULL);
	sml = WHEI / smlnum(matrix->tot_rows, matrix->tot_cols);
	smltab = smlnum(matrix->tot_rows, matrix->tot_cols) - 1;
	corr_blockz(sml, matrix->tot_rows, matrix->tot_cols, matrix->mat);
	while (++y < matrix->tot_rows)
	{
		x = -1;
		tmpy = (WHEI - sml * smltab) * 0.5 + y * sml;
		while (++x < matrix->tot_cols)
		{	
			tmpx = (WWID - sml * smltab) * 0.5 + x * sml;
			blocky[y][x] = ((tmpy * cos((M_PI / 180) * 50) + tmpx * \
			sin((M_PI / 180) * 40)) - tmpy + y * sml - matrix->mat[y][x]) * 0.7;
		}
	}
	corr_blocky(matrix->tot_rows - 1, matrix->tot_cols, blocky);
	return (blocky);
}

void	corr_blockx(int rows, int cols, double **blockx)
{
	double	tab;
	int		x;
	int		y;

	tab = (WWID / 2) - blockx[rows / 2][cols / 2];
	y = 0;
	while (y < rows)
	{
		x = -1;
		while (++x < cols)
			blockx[y][x] += tab;
		y++;
	}
}

double	**creat_blockx(t_matrix *matrix, int y, int x)
{
	double	**blockx;
	int		sml;
	int		smltab;
	int		tempy;
	int		tempx;

	blockx = solo_matrix(matrix->tot_rows, matrix->tot_cols);
	if (!blockx)
		return (NULL);
	sml = WHEI / smlnum(matrix->tot_rows, matrix->tot_cols);
	smltab = smlnum(matrix->tot_rows, matrix->tot_cols) - 1;
	while (++y < matrix->tot_rows)
	{
		x = -1;
		tempy = (WHEI - sml * smltab) * 0.5 + y * sml;
		while (++x < matrix->tot_cols)
		{	
			tempx = (WWID - sml * smltab) * 0.5 + x * sml;
			blockx[y][x] = (tempx * cos((M_PI / 180) * 40) - \
			tempy * sin((M_PI / 180) * 50));
		}
	}
	corr_blockx(matrix->tot_rows, matrix->tot_cols, blockx);
	return (blockx);
}
