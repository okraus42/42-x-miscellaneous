/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:54:16 by okraus            #+#    #+#             */
/*   Updated: 2023/09/24 15:20:30 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/header/libft.h"

//cc bases.c libft.a

int	main(void)
{
	int	a = 42;			//decimal		(no prefix)
	int	b = 0x2A;		//hexadecimal	(0x prefix)
	int	c = 052;		//ocal			(0 prefix)
	int	d = 0b101010;	//binary		(ob prefix)

	printf("Decimal:\n42 = %8d | 0x2A = %8d | 052 = %8d | 0b101010 = %8d\n", a, b, c, d);
	printf("Hexadecimal:\n42 = %#8X | 0x2A = %#8X | 052 = %#8X | 0b101010 = %#8X\n", a, b, c, d);
	printf("Octal:\n42 = %#8o | 0x2A = %#8o | 052 = %#8o | 0b101010 = %#8o\n", a, b, c, d);
	ft_printf("Binary:\n42 = %8.2B | 0x2A = %8.2B | 052 = %8.2B | 0b101010 = %8.2B\n", a, b, c, d);
	ft_printf("\nMix:\n42 = %8.10B |   42 = %8.8B |  42 = %8.16B |       42 = %8.2B\n", 42, 42, 42, 42);
	return (0);
}
