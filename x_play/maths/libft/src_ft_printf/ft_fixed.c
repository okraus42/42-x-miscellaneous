/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fixed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:51:35 by okraus            #+#    #+#             */
/*   Updated: 2023/11/18 15:53:39 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"


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

static int	ft_get_declen(unsigned int fixbits)
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

static void	ft_round_loop(char *str, int *last, int *carry)
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

static void	ft_round_string(char *str)
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
		while (--last && str[last] != '-')
		{
			str[last] = str[last - 1];
		}
		if (str[0] != '-' && last)
			last--;
		str[last] = '1';
	}
}

static void	ft_process_prec(char *s, char *str, int w, int prec)
{
	int	i;

	i = 0;
	while (s[i] && i < w + prec + 1)
	{
		str[i] = s[i];
		i++;
	}
	if (!s[i])
	{
		while (i < w + prec + 1)
		{
			str[i] = '0';
			i++;
		}
	}
	else
	{
		str[i] = s[i];
		ft_round_string(str);
	}
	if (!prec)
	i = 0;
	while (str[++i] != 0)
		if (str[i] == '.')
			str[i] = 0;
}

static int	ft_fix_prec(t_pf_info *data)
{
	int		w;
	int		d;
	int		i;
	char	*str;

	i = 0;
	if (!data->out)
		return (1);
	while (data->out[i] && data->out[i] != '.')
		i++;
	if (!data->out[i])
		return (1);
	w = i++;
	d = 0;
	while (data->out[i + d])
		d++;
	str = ft_calloc(w + data->precision + 3, sizeof(char));
	if (!str)
		return (1);
	ft_process_prec(data->out, str, w, data->precision);
	free(data->out);
	data->out = str;
	return (0);
}

int	ft_process_prcfix(t_pf_info *data)
{
	char	*temp;

	data->out = ft_fixtoa(data->value.ll, data->baselen);
	if (!data->out)
		return (1);
	if (data->out[0] == '-')
	{
		temp = data->out;
		data->out = ft_strdup(&data->out[1]);
		free(temp);
		if (!data->out)
			return (1);
	}
	if (data->flag & PERIOD || (data->flag & ZERO && !(data->flag & 0x84)))
		if (ft_fix_prec(data))
			return (1);
	if (ft_signed_flags(data))
		return (1);
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
			return (1);
	data->outlen = ft_strlen(data->out);
	return (0);
}
