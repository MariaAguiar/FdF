/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:16:22 by mnascime          #+#    #+#             */
/*   Updated: 2023/02/26 08:51:08 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr_p(unsigned long long nb)
{
	char	c;
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = 0;
	if (nb / 16 > 0)
		count += ft_putnbr_p(nb / 16);
	c = base[(nb % 16)];
	count += write(1, &c, 1);
	return (count);
}

static int	ft_putnbr_recur(long int nb, int basis, char *base, char vari)
{
	char	c;
	int		count;

	count = 0;
	if (nb < 0)
	{
		if (vari == 'u' || vari == 'x' || vari == 'X')
			nb = -1 * (UINT_MAX + nb + 1);
		else
			count += write(1, "-", 1);
		count += ft_putnbr_recur(nb * -1, basis, base, vari);
		return (count);
	}
	if (nb / basis > 0)
		count += ft_putnbr_recur(nb / basis, basis, base, vari);
	c = base[(nb % basis)];
	count += write(1, &c, 1);
	return (count);
}

int	ft_putnbr_base(int num, char vari)
{
	char		*base;
	long int	nb;

	nb = (long int)num;
	if (vari == 'i' || vari == 'd' || vari == 'u')
		base = "0123456789";
	else if (vari == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	return (ft_putnbr_recur(nb, ft_strlen(base), base, vari));
}
