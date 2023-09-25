/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_3_xor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:55:23 by okraus            #+#    #+#             */
/*   Updated: 2023/09/24 20:34:52 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/header/libft.h"

int	main(void)
{
	unsigned char	a = 0b00101010;
	unsigned char	b = 0b11111111;
	unsigned char	c = 0b00000000;
	unsigned char	d = 0b00001111;

	ft_printf("a = 0b%+8.2B, b = 0b%+8.2B, c = 0b%+8.2B, d = 0b%+8.2B\n", a, b, c, d);
	ft_printf("a ^ a = 0b%+8.2B\n", a ^ a);
	ft_printf("a ^ b = 0b%+8.2B\n", a ^ b);
	ft_printf("a ^ c = 0b%+8.2B\n", a ^ c);
	ft_printf("a ^ d = 0b%+8.2B\n", a ^ d);
	return (0);
}