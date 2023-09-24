/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_6_rightshift.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:55:43 by okraus            #+#    #+#             */
/*   Updated: 2023/09/24 20:40:53 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/header/libft.h"

int	main(void)
{
	unsigned char	a = 0b00101010;
	unsigned char	b = 0b11111111;
	unsigned char	c = 0b00000000;
	unsigned char	d = 0b00001111;
	int				i;

	ft_printf("a = 0b%+8.2B, b = 0b%+8.2B, c = 0b%+8.2B, d = 0b%+8.2B\n", a, b, c, d);
	i = 0;
	while (++i <= 8)
		ft_printf("a >> %i = 0b%+8.2B, b >> %i = 0b%+8.2B, c >> %i = 0b%+8.2B, d >> %i = 0b%+8.2B\n", i, (unsigned char)(a >> i), i, (unsigned char)(b >> i), i, (unsigned char)(c >> i), i, (unsigned char)(d >> i));
	return (0);
}