/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_colours.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:02:35 by okraus            #+#    #+#             */
/*   Updated: 2023/10/20 16:48:49 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft/header/libft.h"

static unsigned int	get_colour2(int i, unsigned char r1, unsigned char g1,
	unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ((r2) * i + (r1) * (64 - i) ) / 64;
	g = ((g2) * i + (g1) * (64 - i) ) / 64;
	b = ((b2) * i + (b1) * (64 - i) ) / 64;
	return (r << 16 | g << 8 | b);
}

static void	print_colours2(unsigned int c1, unsigned int c2, unsigned int c[65])
{
	unsigned char	r1;
	unsigned char	g1;
	unsigned char	b1;
	unsigned char	r2;
	unsigned char	g2;
	unsigned char	b2;
	int				i;

	r1 = c1 >> 16 & 0xFF;
	g1 = c1 >> 8 & 0xFF;
	b1 = c1 & 0xFF;
	r2 = c2 >> 16 & 0xFF;
	g2 = c2 >> 8 & 0xFF;
	b2 = c2 & 0xFF;
	i = 0;
	while (i < 65)
	{
		c[i] = get_colour2(i, r1, g1, b1, r2, g2, b2);
		ft_printf("%^*C %C", c[i]);
		i++;
	}
	ft_printf("\n");
}

static unsigned int	get_colour(int i, unsigned char r1, unsigned char g1,
	unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)sqrt(((r2 * r2) * i + (r1 * r1) * (64 - i) ) / 64);
	g = (unsigned char)sqrt(((g2 * g2) * i + (g1 * g1) * (64 - i) ) / 64);
	b = (unsigned char)sqrt(((b2 * b2) * i + (b1 * b1) * (64 - i) ) / 64);
	return (r << 16 | g << 8 | b);
}

static void	print_colours(unsigned int c1, unsigned int c2, unsigned int c[65])
{
	unsigned char	r1;
	unsigned char	g1;
	unsigned char	b1;
	unsigned char	r2;
	unsigned char	g2;
	unsigned char	b2;
	int				i;

	r1 = c1 >> 16 & 0xFF;
	g1 = c1 >> 8 & 0xFF;
	b1 = c1 & 0xFF;
	r2 = c2 >> 16 & 0xFF;
	g2 = c2 >> 8 & 0xFF;
	b2 = c2 & 0xFF;
	i = 0;
	while (i < 65)
	{
		c[i] = get_colour(i, r1, g1, b1, r2, g2, b2);
		ft_printf("%^*C %C", c[i]);
		i++;
	}
	ft_printf("\n");
}

static void	ft_fill_clog(unsigned char clog[65536])
{
	int	i;
	int	a;
	int	b;

	i = 0;
	while (i < 65536)
	{
		a = (i >> 8) & 0xFF;
		b = i & 0xFF;
		clog[i] = sqrt(((a * a) + (b * b)) / 2);
		++i;
	}
}

static void	ft_fill_clin(unsigned char clin[65536])
{
	int	i;
	int	a;
	int	b;

	i = 0;
	while (i < 65536)
	{
		a = (i >> 8) & 0xFF;
		b = i & 0xFF;
		clin[i] = (a + b) / 2;
		++i;
	}
}

static void	print_colours3(unsigned int c1, unsigned int c2,
	unsigned char clog[65536], unsigned char clin[65536])
{
	unsigned char	r1;
	unsigned char	g1;
	unsigned char	b1;
	unsigned char	r2;
	unsigned char	g2;
	unsigned char	b2;
	int				i;
	unsigned int	c;

	r1 = c1 >> 16 & 0xFF;
	g1 = c1 >> 8 & 0xFF;
	b1 = c1 & 0xFF;
	r2 = c2 >> 16 & 0xFF;
	g2 = c2 >> 8 & 0xFF;
	b2 = c2 & 0xFF;
	i = 0;
	ft_printf("%^*C  %C", c1);
	while (i < 61)
	{
		c = (clog[r1 << 8 | r2] << 16)
			| (clog[g1 << 8 | g2] << 8)
			| (clog[b1 << 8 | b2]);
		ft_printf("%^*C %C", c);
		i++;
	}
	ft_printf("%^*C  %C\n", c2);
	i = 0;
	ft_printf("%^*C  %C", c1);
	while (i < 61)
	{
		c = (clin[r1 << 8 | r2] << 16)
			| (clin[g1 << 8 | g2] << 8)
			| (clin[b1 << 8 | b2]);
		ft_printf("%^*C %C", c);
		i++;
	}
	ft_printf("%^*C  %C\n", c2);
}

int	main(int argc, char *argv[])
{
	unsigned int c1;
	unsigned int c2;
	unsigned int c[65];
	unsigned char clog[65536];
	unsigned char clin[65536];

	ft_fill_clog(clog);
	ft_fill_clin(clin);
	ft_printf("%X %X \n", clog[0x8020], clin[0x8020]);
	ft_printf("%X %X \n", clog[0x2080], clin[0x2080]);
	if (argc != 3)
		return (ft_dprintf(2, "Incorrect number of arguments\n"));
	else
	{
		c1 = ft_atoi_base(BASE_HEX, argv[1]);
		c2 = ft_atoi_base(BASE_HEX, argv[2]);
	}
	print_colours(c1, c2, c);
	print_colours2(c1, c2, c);
	print_colours3(c1, c2, clog, clin);
	return (0);
}
