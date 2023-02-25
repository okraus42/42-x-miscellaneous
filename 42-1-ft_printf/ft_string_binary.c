/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_hexasmall.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:02:50 by okraus            #+#    #+#             */
/*   Updated: 2023/02/02 15:32:40 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_binlen(unsigned char b)
{
	int	i;

	i = 0;
	if (b <= 0)
		i++;
	while (b)
	{
		b /= 2;
		i++;
	}
	return (i);
}

char	*ft_string_bin(unsigned char b)
{
	char			*str;
	int				i;

	i = ft_binlen(b) - 1;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i + 1] = 0;
	if (b == 0)
		str[i] = '0';
	while (b != 0)
	{
		str[i] = "01"[b % 2];
		b = b / 2;
		i--;
	}
	return (str);
}

int	ft_print_bin_fd(unsigned char b, int fd, t_output *t)
{
	char	*s;
	int		i;

	s = ft_string_bin(b);
	i = 0;
	if (t->hash && b)
		s = ft_strjoin_freeright("0b", s);
	if (t->precision || (t->padsize && t->zero && !t->precision))
	{
		s = ft_precint(s, t);
	}
	if (t->padsize)
		s = ft_padint(s, t);
	while (s[i])
	{
		i += write(fd, &s[i], 1);
	}
	free(s);
	return (i);
}

int	ft_putbin_fd(unsigned char b, int fd, t_output *t)
{
	int		i;

	i = 0;
	if (!b && t->period && !t->precision && t->padsize)
	{
		while (i < t->padsize)
			i += write(1, " ", 1);
		return (i);
	}
	if (!b && t->period && !t->precision)
		return (0);
	i = ft_print_bin_fd(b, fd, t);
	return (i);
}
