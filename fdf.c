/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:59:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/05/31 10:43:14 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*list_to_matrix(t_list **list)
{
	t_matrix	*matrix;
	t_node		*cur;
	int			i;

	matrix = init_matrix((*list)->tot_rows, (*list)->tot_cols);
	cur = (*list)->head;
	i = 0;
	while (i < matrix->tot_rows)
	{
		matrix->mat[i] = cur->arr;
		cur->arr = NULL;
		cur = cur->next;
		i++;
	}
	destroy_list(list);
	return (matrix);
}

double	*creat_arr(char	*line, t_list *list)
{
	char	**split;
	double	*arr;
	int		i;

	split = ft_split(line, ' ');
	i = 0;
	while (split[i] && split[i][0] != '\n' && split[i][0] != '\0')
		i++;
	arr = malloc(sizeof(*arr) * i);
	if (!arr)
		return (0);
	list->tot_cols = i;
	i = 0;
	while (i < list->tot_cols)
	{
		if (split[i])
			arr[i] = ft_atoi(split[i]);
		i++;
	}
	destroy_split(&split);
	return (arr);
}

t_list	*file_to_dll(int fd)
{
	t_list	*list;
	char	*line;

	list = init_list();
	if (!list)
		return (NULL);
	line = (char *)1;
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			insert_tail(list, creat_arr(line, list));
			free(line);
		}
	}
	return (list);
}

int	main(int ac, char *av[])
{
	t_list		*list;
	t_matrix	*matrix;
	int			fd;

	if (ac == 2 && ft_strnstr(&av[1][ft_strlen(av[1]) \
	- 4], ".fdf", ft_strlen(av[1])))
	{
		fd = open(av[1], O_RDONLY, 0777);
		if (fd <= 0)
			return (0);
		list = file_to_dll(fd);
		if (list)
		{
			matrix = list_to_matrix(&list);
			display_in_canvas(matrix);
		}
		close(fd);
	}
	return (0);
}
