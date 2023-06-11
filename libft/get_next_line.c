/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:02:18 by mnascime          #+#    #+#             */
/*   Updated: 2023/03/27 20:19:27 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	i = 1;
	while (i && (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0))
	{
		line = ft_strjoin(line, buffer);
		i = clean_buf(buffer);
	}
	return (line);
}
