/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:51:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/06 16:35:28 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <math.h>
# include "./mlx_linux/mlx.h"
# include "./libft/libft.h"

# define WWID 1920
# define WHEI 1080
# define ESC 65307

typedef struct s_node	t_node;

typedef struct s_node
{
	double			*arr;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		tot_rows;
	int		tot_cols;
}	t_list;

typedef struct s_matrix
{
	double	**mat;
	int		tot_rows;
	int		tot_cols;
}	t_matrix;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_matrix	*matrix;
}	t_data;

typedef struct s_vector
{
	int	xi;
	int	yi;
	int	xf;
	int	yf;
}	t_vector;

// Blocks
int			smlnum(int rows, int cols);
void		corr_blocky(int rows, int cols, double **blocky);
double		**creat_blocky(t_matrix *matrix, int y, int x);
void		corr_blockx(int rows, int cols, double **blockx);
double		**creat_blockx(t_matrix *matrix, int y, int x);

// Display
int			quits(t_data *img);
int			read_keys(int key_pressed, void *param);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_line(t_data *data, t_vector *vector, int zi, int zf);
void		display_in_canvas(t_matrix *matrix);

// Draw utils
void		begin_coord(t_vector *vector, int x, int y);
void		end_coord(t_vector *vector, int x, int y);
void		corr_blockz(int tab, int rows, int cols, double **blockz);
int			max_z(int rows, int cols, double **blockz);
int			min_z(int rows, int cols, double **blockz);

// Draw
void		draw_midlines(t_data *img, t_matrix *mat, double **bx, double **by);
int			recolor(int zi, int rf, int gf, int bf);
void		colorize(t_matrix *matrix);
void		draw_hedges(t_data *img, t_matrix *mat, double **bx, double **by);
void		draw_vedges(t_data *img, t_matrix *mat, double **bx, double **by);

// Init_End
t_node		*init_node(void);
t_list		*init_list(void);
t_matrix	*init_matrix(int tot_rows, int tot_cols);
void		destroy_list(t_list **list);
void		destroy_matrix(t_matrix **mat);

// Scale
void		corr_b(int rows, int cols, double corr, double **block);
void		rescale(t_matrix *mat, double **bx, double **by);
int			bignum(int first, int second);

// Utils
void		insert_tail(t_list *list, double *data);
void		destroy_split(char ***split_location);
double		**solo_matrix(int rows, int cols);
void		free_blocks(int rows, double **blockx, double **blocky);

// fdf
t_matrix	*list_to_matrix(t_list **list);
t_list		*file_to_dll(int fd);

#endif
