/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:04:32 by okraus            #+#    #+#             */
/*   Updated: 2023/02/22 18:37:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*ft_print_memory(void *addr, int fd, unsigned int size);

//void	*ft_print_memory_2(void *addr, int fd, unsigned int size);

static int	ft_put_bit(const unsigned char t, int fd)
{
	if (t & 0x80)
		write(fd, "1", 1);
	else
		write(fd, "0", 1);
	return (1);
}

int	ft_put_bin(const unsigned char c, int fd)
{
	unsigned char	t;
	int				i;

	i = 8;
	t = c;
	while (i != 4)
	{
		ft_put_bit(t, fd);
		i--;
		t <<= 1;
	}
	write (fd, " ", 1);
	while (i)
	{
		ft_put_bit(t, fd);
		i--;
		t <<= 1;
	}
	write (fd, "\n", 1);
	return (9);
}

static void	ft_put_hex(void *addr, int fd)
{
	unsigned int	i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *) addr;
	write(fd, &"0123456789abcdef"[s[i] / 16], 1);
	write(fd, &"0123456789abcdef"[s[i] % 16], 1);

}

int	main(void)
{
	unsigned char	a[17] = "0123456789abcdef";
	unsigned char	b;
	unsigned char	s[200] = "0123456789abc\200defghijkl\n\t\vafdadsfhaghag";
	unsigned int	u;
	unsigned int	*x;
	void			*c;
	int				fd;

	fd = 1;
	b = 'b';
	printf("a[5] = %c\n", a[5]);
	printf("*(a + 5) = %c\n", *(a + 5));
	printf("5[a] = %c\n", 5[a]);
	printf("*(5 + a) = %c\n\n", *(5 + a));
	printf("b: %c | %x\n\n", b, b);
	b = b & 'B';
	printf("b = b & 'B';\n");
	ft_put_bin(b, fd);
	printf("b: %c | %x\n\n", b, b);
	b = b & 0xFF;
	printf("b = b & 0xFF;\n");
	ft_put_bin(b, fd);
	printf("b: %c | %x\n\n", b, b);
	b = b | 0x20;
	printf("b = b | 0x20;\n");
	ft_put_bin(b, fd);
	printf("b: %c | %x\n\n", b, b);
	b >>= 1;
	printf("b >>= 1;\n");
	ft_put_bin(b, fd);
	printf("b: %c | %x\n\n", b, b);
	b <<= 2;
	printf("b <<= 2;\n");
	ft_put_bin(b, fd);
	printf("b: %c | %x\n\n", b, b);
	b = ~b;
	printf("b = ~b;\n");
	ft_put_bin(b, fd);
	printf("b: %c | %x\n\n", b, b);
	u = 0xA1B2C3D4;
	x = &u;
	printf("u = 0xA1B2C3D4;\n");
	ft_put_hex(&u, 1);
	ft_put_hex((void *)&u + 1, 1);
	ft_put_hex((void *)&u + 2, 1);
	ft_put_hex((void *)&u + 3, 1);
	write (1, "\n", 1);
	b = *(unsigned char *)(((void *)(&u)) + 3);
	ft_put_bin(b, 1);
	b = *(unsigned char *)(((void *)(&u)) + 2);
	ft_put_bin(b, 1);
	b = *(unsigned char *)(((void *)(&u)) + 1);
	ft_put_bin(b, 1);
	b = *(unsigned char *)&u;
	ft_put_bin(b, 1);
	write (1, "\n", 1);
	printf("u: %X\n\n", u);
	c = ft_print_memory(&s[0], 1, 200);
	return (0);
}
/*
OTHER STUFF

	unsigned char	*s2;
	void			*c;
	s2 = malloc((long)4000000001);
	s2[30000] = '9';
	s2[300000] = 'a';
	s2[3000000] = 'b';
	s2[30000000] = 'c';
	s2[300000000] = 'd';
	s2[3000000000] = 'e';
	c = ft_print_memory_2(&s2[0], 1, (unsigned int)4000000000);
*/
