/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam_swap_bits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:54:16 by okraus            #+#    #+#             */
/*   Updated: 2023/09/24 16:25:45 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int i = 1;

	i <<= 8;
	while (i >>= 1)
		(octet & i) ? write(1, "1", 1) : write(1, "0", 1);
	write(1, "\n", 1);
}

unsigned char swap_bits1a(unsigned char octet)
{
	unsigned char	byte;

	byte = ((octet & 0b11110000) >> 4);
	byte |= ((octet & 0b00001111) << 4);
	return (byte);
}

unsigned char swap_bits1b(unsigned char octet)
{
	unsigned char	byte;

	byte = ((octet & 0xF0) >> 4);
	byte |= ((octet & 0xF) << 4);
	return (byte);
}

unsigned char swap_bits1c(unsigned char octet)
{
	unsigned char	byte;

	byte = ((octet & 240) >> 4);
	byte |= ((octet & 15) << 4);
	return (byte);
}

unsigned char swap_bits2(unsigned char octet)
{
	unsigned char	byte;

	byte = ((octet & 0xF0) >> 4) | ((octet & 0xF) << 4);
	return (byte);
}

unsigned char swap_bits3(unsigned char octet)
{
	return ((octet << 4) | (octet >> 4));
}

int	main(void)
{
	unsigned char	octet = 0b00101010;
	unsigned char	byte = 0;

	write(1, "1a:\n", 4);
	print_bits(octet);
	byte = swap_bits1a(octet);
	print_bits(byte);
	write(1, "\n", 1);
	write(1, "1b:\n", 4);
	print_bits(octet);
	byte = swap_bits1b(octet);
	print_bits(byte);
	write(1, "\n", 1);
	write(1, "1c:\n", 4);
	print_bits(octet);
	byte = swap_bits1c(octet);
	print_bits(byte);
	write(1, "\n", 1);
	write(1, "2: \n", 4);
	print_bits(octet);
	byte = swap_bits2(octet);
	print_bits(byte);
	write(1, "\n", 1);
	write(1, "3: \n", 4);
	print_bits(octet);
	byte = swap_bits3(octet);
	print_bits(byte);
	write(1, "\n", 1);
	return (0);
}