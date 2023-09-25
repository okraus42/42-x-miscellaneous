/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_endianness.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:15:10 by okraus            #+#    #+#             */
/*   Updated: 2023/09/25 13:46:32 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/header/libft.h"

/*Endianness is primarily expressed as big-endian (BE) or little-endian (LE).
A big-endian system stores the most significant byte of a word at the smallest
memory address and the least significant byte at the largest.
A little-endian system, in contrast, stores the least-significant byte
at the smallest address*/
int	main(void)
{
	int		hex[4] = {0xaabbccdd, 0x23456789, 0x00000000, 0xffffffff};
	int		hex2[4] = {0x00001234, 0x00000000, 0xFEDC0000, 0x00000000};
	int		i = -1;
	char	*byte = (char *)hex;

	ft_print_memory_plus(hex, 1, 16);
	while (++i < 16)
	{
		if (~i & 0b10 && ~i & 0b01)
			ft_printf("%X\n", *(int *)byte);
		ft_printf("[%2i]%p: <%2X> <%+8.2B>\n", i, byte, (unsigned char)*byte, (unsigned char)*byte);
		if (i & 0b10 && i & 0b01 && i != 15)
			ft_printf("\n");
		byte++;
	}
	ft_printf("\n");
	ft_print_memory_plus(hex2, 1, 16);
	byte = (char *)hex2;
	i = -1;
	while (++i < 16)
	{
		if (~i & 0b10 && ~i & 0b01)
			ft_printf("%X\n", *(int *)byte);
		ft_printf("[%2i]%p: <%2X> <%+8.2B>\n", i, byte, (unsigned char)*byte, (unsigned char)*byte);
		if (i & 0b10 && i & 0b01 && i != 15)
			ft_printf("\n");
		byte++;
	}
	return (0);
}