/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixedpoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:29:03 by okraus            #+#    #+#             */
/*   Updated: 2023/11/08 17:22:23 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/header/libft.h"

static char	*ft_fixstr(long long n, int declen, char* whole, char *decimal)
{
	int		i;
	int		j;
	char	*str;
	int		sign;

	sign = 0;
	if (n < 0)
		++sign;
	str = ft_calloc(ft_strlen(whole) + declen + sign + 2, 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (sign)
	{
		str[i] = '-';
		++i;
	}
	while (whole[j])
	{
		str[i + j] = whole[j];
		++j;
	}
	str[i + j] = '.';
	i = i + j + 1;
	j = 0;
	while (ft_strlen(decimal) + j < (unsigned long)declen)
	{
		str[i + j] = '0';
		++j;
	}
	i = i + j;
	j = 0;
	while (decimal[j])
	{
		str[i + j] = decimal[j];
		++j;
	}
	return (str);
}

char	*ft_fixtoa(long long n, unsigned int fixbits)
{
	char				*whole;
	char				*decimal;
	char				*str;
	long long			w;
	unsigned long long	d;
	unsigned int					i;
	int					declen;
	long long			j;
	unsigned long long	fives;

	if (!fixbits || fixbits > 16)
		fixbits = 8;
	i = 0;
	j = 1;
	fives = 1;
	while (++i <= fixbits)
	{
		j *= 2;
		fives *= 5;
	}
	--j;
	decimal = ft_ultoa_base(j * fives, "0123456789", 10);
	if (!decimal)
		return (NULL);
	declen = ft_strlen(decimal);
	free (decimal);
	if (n >= 0)
	{
		w = n >> fixbits;
		d = n & j;
	}
	else
	{
		w = (-n) >> fixbits;
		d = (-n) & j;
	}
	d *= fives;
	whole = ft_litoa(w);
	if (!whole)
		return (NULL);
	decimal = ft_ultoa_base(d, "0123456789", 10);
	if (!decimal)
		return (NULL);
	str = ft_fixstr(n, declen, whole, decimal);
	free (whole);
	free (decimal);
	return (str);
}

//need to add rounding for precision
int	main(int ac, char *av[])
{
	char *s;

	if (ac != 3)
		return (5);
	s = ft_fixtoa(ft_latoi(av[1]), ft_atoi(av[2]));
	ft_printf("%s\n", s);
	free(s);
	return (0);
	
}