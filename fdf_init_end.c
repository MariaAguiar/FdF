/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/06 05:28:08 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->arr = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_list	*init_list(void)
{
	t_list	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->tot_rows = 0;
	list->tot_cols = 0;
	return (list);
}

t_matrix	*init_matrix(int tot_rows, int tot_cols)
{
	t_matrix	*matrix;

	matrix = malloc(sizeof(*matrix));
	if (!matrix)
		return (NULL);
	matrix->tot_rows = tot_rows;
	matrix->tot_cols = tot_cols;
	matrix->mat = malloc(sizeof(*(matrix->mat)) * tot_rows);
	if (!matrix->mat)
	{
		free(matrix);
		return (NULL);
	}
	return (matrix);
}

void	destroy_list(t_list **list)
{
	t_node	*del;
	t_node	*next;

	if (!list || !(*list))
		return ;
	next = NULL;
	del = (*list)->head;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
	free(*list);
	*list = NULL;
}

void	destroy_matrix(t_matrix **mat)
{
	double	**matrix;
	int		i;

	matrix = (*mat)->mat;
	i = -1;
	while (++i < (*mat)->tot_rows)
		free(matrix[i]);
	free(matrix);
	(*mat)->mat = NULL;
	free((*mat));
	*mat = NULL;
}
