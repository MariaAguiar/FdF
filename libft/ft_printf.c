/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:16:20 by mnascime          #+#    #+#             */
/*   Updated: 2022/05/29 19:09:37 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static int	ft_putstr_prtf(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr_prtf("(null)"));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

static char	*ft_strchr_prtf(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

static int	ft_print_check(char s)
{
	const char	*set;

	set = "cspdiuxX%";
	if (ft_strchr_prtf(set, s))
		return (1);
	return (0);
}

static int	ft_print_choice(va_list *args, char s)
{
	int	f;

	f = 0;
	if (s == 'c')
		f = ft_putchar(va_arg(*args, int));
	else if (s == 's')
		f = ft_putstr_prtf(va_arg(*args, char *));
	else if (s == 'u')
		f = ft_putnbr_base((unsigned int)va_arg(*args, int), s);
	else if (s == '%')
		f = ft_putchar(s);
	else if (s == 'p')
	{
		ft_putchar('0');
		ft_putchar('x');
		f = 2 + ft_putnbr_p(va_arg(*args, unsigned long long));
	}
	else
		f = ft_putnbr_base(va_arg(*args, int), s);
	return (f);
}

int	ft_printf(const char *s, ...)
{
	int		f;
	va_list	arguments;

	f = 0;
	va_start(arguments, s);
	while (*s)
	{
		if (*s == '%' && ft_print_check(*(s + 1)))
		{
			s++;
			f += ft_print_choice(&arguments, *s);
		}
		else
			f += ft_putchar(*s);
		s++;
	}
	va_end(arguments);
	return (f);
}
