/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_colours.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:02:35 by okraus            #+#    #+#             */
/*   Updated: 2023/10/19 17:41:00 by okraus           ###   ########.fr       */
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

	r = ((r1) * i + (r2) * (63 - i) ) / 64;
	g = ((g1) * i + (g2) * (63 - i) ) / 64;
	b = ((b1) * i + (b2) * (63 - i) ) / 64;
	return (r << 16 | g << 8 | b);
}

static void	print_colours2(unsigned int c1, unsigned int c2, unsigned int c[64])
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
	while (i < 64)
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

	r = (unsigned char)sqrt(((r1 * r1) * i + (r2 * r2) * (63 - i) ) / 64);
	g = (unsigned char)sqrt(((g1 * g1) * i + (g2 * g2) * (63 - i) ) / 64);
	b = (unsigned char)sqrt(((b1 * b1) * i + (b2 * b2) * (63 - i) ) / 64);
	return (r << 16 | g << 8 | b);
}

static void	print_colours(unsigned int c1, unsigned int c2, unsigned int c[64])
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
	while (i < 64)
	{
		c[i] = get_colour(i, r1, g1, b1, r2, g2, b2);
		ft_printf("%^*C %C", c[i]);
		i++;
	}
	ft_printf("\n");
}

int	main(int argc, char *argv[])
{
	unsigned int c1;
	unsigned int c2;
	unsigned int c[64];

	if (argc != 3)
		return (ft_dprintf(2, "Incorrect number of arguments\n"));
	else
	{
		c1 = ft_atoi_base(BASE_HEX, argv[1]);
		c2 = ft_atoi_base(BASE_HEX, argv[2]);
	}
	print_colours(c1, c2, c);
	print_colours2(c1, c2, c);
	return (0);
}
