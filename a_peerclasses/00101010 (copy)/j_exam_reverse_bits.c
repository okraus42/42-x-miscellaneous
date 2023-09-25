/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam_reverse_bits.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:54:16 by okraus            #+#    #+#             */
/*   Updated: 2023/09/24 16:20:37 by okraus           ###   ########.fr       */
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

unsigned char reverse_bits0(unsigned char octet)
{
	unsigned char	byte;

	byte = (octet & 0b00000001) << 7;
	byte |= (octet & 0b00000010) << 5;
	byte |= (octet & 0b00000100) << 3;
	byte |= (octet & 0b00001000) << 1;
	byte |= (octet & 0b00010000) >> 1;
	byte |= (octet & 0b00100000) >> 3;
	byte |= (octet & 0b01000000) >> 5;
	byte |= (octet & 0b10000000) >> 7;
	return (byte);
}

unsigned char reverse_bits1a(unsigned char octet)
{
	octet = ((octet & 0b10101010) >> 1) | ((octet & 0b01010101) << 1);
	octet = ((octet & 0b11001100) >> 2) | ((octet & 0b00110011) << 2);
	return (((octet & 0b11110000 )>> 4) | ((octet & 0b00001111) << 4));
}

unsigned char reverse_bits1b(unsigned char octet)
{
	octet = ((octet & 170) >> 1) | ((octet & 85) << 1);
	octet = ((octet & 204) >> 2) | ((octet & 51) << 2);
	return ((octet >> 4) | (octet << 4));
}

unsigned char reverse_bits1c(unsigned char octet)
{
	octet = ((octet & 0xaa) >> 1) | ((octet & 0x55) << 1);
	octet = ((octet & 0xcc) >> 2) | ((octet & 0x33) << 2);
	return ((octet >> 4) | (octet << 4));
}

unsigned char reverse_bits2(unsigned char octet)
{
	static const unsigned char BitReverseTable16[] = {0b0000, 0b1000, 0b0100, 0b1100, 0b0010, 0b1010, 0b0110, 0b1110, 0b0001, 0b1001, 0b0101, 0b1101, 0b0011, 0b1011, 0b0111, 0b1111};
	return (BitReverseTable16[(octet & 0xF)] << 4 | BitReverseTable16[(octet >> 4)]);
}

unsigned char reverse_bits3(unsigned char octet)
{
	static const unsigned char BitReverseTable4[] = {0b00, 0b10, 0b01, 0b11};
	return (BitReverseTable4[(octet & 0x3)] << 6 | BitReverseTable4[((octet & 0xC) >> 2)] << 4 | BitReverseTable4[((octet & 0x30) >> 4)] << 2 | BitReverseTable4[((octet & 0xC0) >> 6)]);
}

int	main(void)
{
	unsigned char	octet = 0b00101010;
	unsigned char	byte = 0;

	write(1, "0: \n", 4);
	print_bits(octet);
	byte = reverse_bits0(octet);
	print_bits(byte);
	write(1, "\n", 1);
	write(1, "1a:\n", 4);
	print_bits(octet);
	byte = reverse_bits1a(octet);
	print_bits(byte);
	write(1, "\n", 1);
	write(1, "1b:\n", 4);
	print_bits(octet);
	byte = reverse_bits1b(octet);
	print_bits(byte);
	write(1, "\n", 1);
	write(1, "1c:\n", 4);
	print_bits(octet);
	byte = reverse_bits1c(octet);
	print_bits(byte);
	write(1, "\n", 1);
	write(1, "2: \n", 4);
	print_bits(octet);
	byte = reverse_bits2(octet);
	print_bits(byte);
	write(1, "\n", 1);
	write(1, "3: \n", 4);
	print_bits(octet);
	byte = reverse_bits3(octet);
	print_bits(byte);
	return (0);
}