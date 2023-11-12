/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixedpoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:29:03 by okraus            #+#    #+#             */
/*   Updated: 2023/11/12 17:18:55 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/header/libft.h"

static void	ft_fixwhole(int *i, int *j, char *str, char *whole)
{
	while (whole[*j])
	{
		str[*i + *j] = whole[*j];
		++(*j);
	}
	str[*i + *j] = '.';
	*i = *i + *j + 1;
	*j = 0;
}

static void	ft_fixdecimal(int *i, int *j, char *str, char *decimal)
{
	*i = *i + *j;
	*j = 0;
	while (decimal[*j])
	{
		str[*i + *j] = decimal[*j];
		++(*j);
	}
}

static char	*ft_fixstr(long long n, int declen, char *whole, char *decimal)
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
		str[i++] = '-';
	ft_fixwhole(&i, &j, str, whole);
	while (ft_strlen(decimal) + j < (unsigned long)declen)
	{
		str[i + j] = '0';
		++j;
	}
	ft_fixdecimal(&i, &j, str, decimal);
	return (str);
}

int	ft_get_declen(unsigned int fixbits)
{
	unsigned int		i;
	int					declen;
	long long			j;
	unsigned long long	fives;
	char				*decimal;

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
		return (-1);
	declen = ft_strlen(decimal);
	free(decimal);
	return (declen);
}

static void	ft_get_dw(long long n, unsigned int fb, char **dec, char **wh)
{
	long long			w[2];
	unsigned long long	d;
	unsigned int		i;
	unsigned long long	fives;

	w[1] = 1;
	fives = 1;
	i = 0;
	while (++i <= fb)
	{
		w[1] *= 2;
		fives *= 5;
	}
	--w[1];
	if (n >= 0)
		w[0] = n >> fb;
	else
		w[0] = (-n) >> fb;
	if (n >= 0)
		d = n & w[1];
	else
		d = (-n) & w[1];
	d *= fives;
	*wh = ft_litoa(w[0]);
	*dec = ft_ultoa_base(d, "0123456789", 10);
}

char	*ft_fixtoa(long long n, unsigned int fixbits)
{
	char				*whole;
	char				*decimal;
	char				*str;
	int					declen;

	if (!fixbits || fixbits > 16)
		fixbits = 8;
	declen = ft_get_declen(fixbits);
	if (declen < 0)
		return (NULL);
	whole = NULL;
	decimal = NULL;
	ft_get_dw(n, fixbits, &decimal, &whole);
	if (!whole && !decimal)
		return (NULL);
	else if (!whole)
		return (free(decimal), NULL);
	else if (!decimal)
		return (free(whole), NULL);
	str = ft_fixstr(n, declen, whole, decimal);
	free (whole);
	free (decimal);
	return (str);
}

void	ft_round_loop(char *str, int *last, int *carry)
{
	while (*carry && *last && str[*last - 1] != '-')
	{
		*carry = 0;
		--(*last);
		if (str[(*last)] == '9')
		{
			str[(*last)] = '0';
			*carry = 1;
		}
		else if (str[(*last)] != '.' && str[(*last)] != '-')
			str[(*last)]++;
		else if (str[(*last)] == '.')
			*carry = 1;
	}
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
	ft_round_loop(str, &last, &carry);
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

void	ft_process_prec(char *s, char *str, int w, int prec)
{
	int	i;

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
	ft_process_prec(s, str, w, prec);
	free(s);
	return (str);
}

//need to add rounding for precision
//s = ft_fixtoa(ft_latoi(av[1]), ft_atoi(av[2]));
// +0.5 for positive - 0.5 for negative
// multiply by 2^bits
//
//FLOAT TO FIX (Double to fix)
int	main(int ac, char *av[])
{
	char	*s;

	if (ac != 4)
		return (5);
	if (atof(av[1]) >= 0)
		s = ft_fixtoa((long long)(((atof(av[1])) * 65536) + 0.5), ft_atoi(av[2]));
	else
		s = ft_fixtoa(-9223372036854775807 - 1/*(long long)(((atof(av[1])) * 256) - 0.5)*/, ft_atoi(av[2]));
	s = ft_fix_prec(s, ft_atoi(av[3]));
	ft_printf("%s\n", s);
	free(s);
	return (0);
}
