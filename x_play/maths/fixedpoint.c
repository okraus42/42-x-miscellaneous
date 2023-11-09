/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixedpoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:29:03 by okraus            #+#    #+#             */
/*   Updated: 2023/11/09 18:08:59 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
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

void	ft_round_string(char *str)
{
	int	last;
	int	carry;

	last = 0;
	carry = 0;
	while (str[last])
		last++;
	--last;
	if (ft_strchr("56789", str[last]))
		carry = 1;
	while (carry && last && str[last - 1] != '-')
	{
		carry = 0;
		--last;
		if (str[last] == '9')
		{
			str[last] = '0';
			carry = 1;
		}
		else if (str[last] != '.' && str[last] != '-')
			str[last]++;
		else if (str[last] == '.')
			carry = 1;
	}
	while (str[last])
		last++;
	if (!carry)
		str[--last] = '\0';
	else
	{
		while (--last - 1 && str[last] != '-')
			str[last] = str[last - 1];
		if (str[0] != '-')
			last--;	
		str[last] = '1';
	}
}

char	*ft_fix_prec(char *s, int prec)
{
	int		w;
	int		d;
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '.')
		i++;
	if (!s[i])
		return (NULL);
	w = i++;
	d = 0;
	while (s[i + d])
		d++;
	str = ft_calloc(w + prec + 3, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && i < w + prec + 2)
	{
		str[i] = s[i];
		i++;
	}
	if (!s[i])
	{
		while (i < w + prec + 2)
		{
			str[i] = '0';
			i++;
		}
	}
	else
		ft_round_string(str);
	free(s);
	return (str);
}

//need to add rounding for precision
int	main(int ac, char *av[])
{
	char *s;

	if (ac != 4)
		return (5);
	//s = ft_fixtoa(ft_latoi(av[1]), ft_atoi(av[2]));
	// +0.5 for positive - 0.5 for negative
	// multiply by 2^bits
	//
	//FLOAT TO FIX (Double to fix)
	if (atof(av[1]) >= 0)
		s = ft_fixtoa((int)(((atof(av[1])) * 256) + 0.5), ft_atoi(av[2]));
	else
		s = ft_fixtoa((int)(((atof(av[1])) * 256) - 0.5), ft_atoi(av[2]));
	s = ft_fix_prec(s, ft_atoi(av[3]));
	ft_printf("%s\n", s);
	free(s);
	return (0);
	
}
