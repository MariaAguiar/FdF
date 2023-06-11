/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:38:40 by mnascime          #+#    #+#             */
/*   Updated: 2023/05/07 14:43:07 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	f;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	f = i;
	i = ft_strlen(s1);
	while (i > f && ft_strchr(set, s1[i]))
		i--;
	j = i + 1;
	ptr = malloc(sizeof(char) * (j - f + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (f < j)
		ptr[i++] = s1[f++];
	ptr[i] = '\0';
	return (ptr);
}
