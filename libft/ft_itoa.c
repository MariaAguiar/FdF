/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:39:01 by mnascime          #+#    #+#             */
/*   Updated: 2022/04/03 17:39:02 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static int	get_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;

	i = get_len(n);
	s = malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	s[0] = '0';
	s[i] = '\0';
	if (n == -2147483648)
	{
		s[--i] = '8';
		n = n / 10;
	}
	if (n < 0)
	{
		s[0] = '-';
		n = n * -1;
	}
	while (n > 0 && i > 0)
	{
		s[--i] = n % 10 + '0';
		n = n / 10;
	}
	return (s);
}
