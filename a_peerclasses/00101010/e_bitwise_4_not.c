/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_4_not.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:55:28 by okraus            #+#    #+#             */
/*   Updated: 2023/09/24 20:34:56 by okraus           ###   ########.fr       */
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
	ft_printf("~a = 0b%+8.2B\n", (unsigned char)~a);
	ft_printf("~b = 0b%+8.2B\n", (unsigned char)~b);
	ft_printf("~c = 0b%+8.2B\n", (unsigned char)~c);
	ft_printf("~d = 0b%+8.2B\n", (unsigned char)~d);
	return (0);
}