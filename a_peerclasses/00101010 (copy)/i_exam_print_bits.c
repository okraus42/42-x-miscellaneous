/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam_print_bits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:54:16 by okraus            #+#    #+#             */
/*   Updated: 2023/09/24 16:19:21 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_bits1a(unsigned char octet)
{
	if (octet & 0b10000000)  //0x80, 128
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0b1000000)  //0x40, 64
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0b100000)	//0x20, 32
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0b10000)	//0x10, 16
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0b1000)		//0x8, 8
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0b100)		//0x4, 4
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0b10)		//0x2, 2
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0b1)		//0x1, 1
		write(1, "1", 1);
	else
		write(1, "0", 1);
}

void	print_bits1b(unsigned char octet)
{
	if (octet & 0x80)  //0x80, 128
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0x40)  //0x40, 64
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0x20)	//0x20, 32
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0x10)	//0x10, 16
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0x8)		//0x8, 8
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0x4)		//0x4, 4
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0x2)		//0x2, 2
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 0x1)		//0x1, 1
		write(1, "1", 1);
	else
		write(1, "0", 1);
}

void	print_bits1c(unsigned char octet)
{
	if (octet & 128)  //0x80, 128
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 64)  //0x40, 64
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 32)	//0x20, 32
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 16)	//0x10, 16
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 8)		//0x8, 8
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 4)		//0x4, 4
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 2)		//0x2, 2
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (octet & 1)		//0x1, 1
		write(1, "1", 1);
	else
		write(1, "0", 1);
}

void	print_bits2(unsigned char octet)
{
	int	i;

	i = 8;
	while (i)
	{
		if (octet & 0b10000000)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		octet <<= 1;
		i--;
	}
}

void	print_bits3(unsigned char octet)
{
	int i = 1;

	i <<= 8;
	while (i >>= 1)
	{
		if (octet & i)
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
}

void	print_bits4(unsigned char octet)
{
	int i = 1;

	i <<= 8;
	while (i >>= 1)
		(octet & i) ? write(1, "1", 1) : write(1, "0", 1);
}

int	main(void)
{
	unsigned char octet = 0b00101010;

	write(1, "1a:\n", 4);
	print_bits1a(octet);
	write(1, "\n", 1);
	write(1, "1b:\n", 4);
	print_bits1b(octet);
	write(1, "\n", 1);
	write(1, "1c:\n", 4);
	print_bits1c(octet);
	write(1, "\n", 1);
	write(1, "2: \n", 4);
	print_bits2(octet);
	write(1, "\n", 1);
	write(1, "3: \n", 4);
	print_bits3(octet);
	write(1, "\n", 1);
	write(1, "4: \n", 4);
	print_bits4(octet);
	write(1, "\n", 1);
	return (0);
}
