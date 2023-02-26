/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:42:15 by okraus            #+#    #+#             */
/*   Updated: 2023/02/22 18:29:50 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

static void	ft_format_plus(int fd, unsigned char c)
{
	if (c == 0)
		fd = 1;
	else if (c < 32 || c == 127)
		write(fd, "\033[37;44m\0\0\0\0\0\0\0\0", 15);
	else if (c < 127)
		write(fd, "\033[30;42m\0\0\0\0\0\0\0\0", 15);
	else
		write(fd, "\033[30;41m\0\0\0\0\0\0\0\0", 14);
}

static void	ft_putaddr_fd(uintptr_t mem, int fd, unsigned int k)
{
	unsigned long	f;
	unsigned int	i;
	unsigned char	c;
	unsigned char	*s;

	i = 0;
	c = 0;
	s = (unsigned char *) mem;
	f = 0xF000000000000000;
	while (i < 16 && k)
	{
		if (s[i] > c)
			c = s[i];
		if (s[i] && s[i] < 32 && c < 127)
			c = 127;
		i++;
	}
	i = 0;
	ft_format_plus(fd, c);
	while (i < 16)
	{
		write(fd, &"0123456789abcdef"[((mem & f) / 0x1000000000000000)], 1);
		mem <<= 4;
		i++;
	}
}

static void	ft_put_hex(void *addr, int fd, unsigned int k)
{
	unsigned int	i;
	unsigned char	*s;

	write(fd, ":\033[0m \0\0\0\0\0\0\0\0", 15);
	i = 0;
	s = (unsigned char *) addr;
	while (i < 16)
	{
		if (k)
		{
			ft_format_plus(fd, s[i]);
			write(fd, &"0123456789abcdef"[s[i] / 16], 1);
			write(fd, &"0123456789abcdef"[s[i] % 16], 1);
			write(fd, "\033[0m\0\0\0\0\0\0\0\0\0\0\0\0", 14);
			k--;
		}
		else
			write(fd, "\033[0m  \0\0\0\0\0\0\0\0\0\0\0\0", 15);
		if (i & 1)
			write(fd, "\033[0m \0\0\0\0\0\0\0\0\0\0\0\0", 15);
		i++;
	}
}

static void	ft_put_char(void *addr, int fd, unsigned int k)
{
	unsigned int	i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *) addr;
	while (k && i < 16)
	{
		ft_format_plus(fd, s[i]);
		if (s[i] > 31 && s[i] < 127)
		{
			write(fd, &s[i], 1);
			write(fd, "\033[0m\0\0\0\0\0\0\0\0\0\0\0\0", 15);
		}
		else
			write(fd, ".\033[0m\0\0\0\0\0\0\0\0\0\0\0\0", 16);
		k--;
		i++;
	}
	write(fd, "\033[0m\0\0\0\0\0\0\0\0\0\0\0\0", 15);
	write(fd, "\n", 1);
}

void	*ft_print_memory_plus(void *addr, int fd, unsigned int size)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	while (i < size)
	{
		k = size - i;
		ft_putaddr_fd((uintptr_t) addr + i, fd, k);
		ft_put_hex(addr + i, fd, k);
		ft_put_char(addr + i, fd, k);
		i += 16;
	}
	return (addr);
}

/*
static void	ft_put_char_2(void *addr, int fd, unsigned int k)
{
	unsigned int	i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *) addr;
	while (k && i < 16)
	{
		if (s[i])
		{
			ft_putaddr_fd((uintptr_t) addr + i, fd);
			write(fd, &s[i], 1);
			write(fd, "\n", 1);
		}
		k--;
		i++;
	}
}

void	*ft_print_memory_2(void *addr, int fd, unsigned int size)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	while (i < size)
	{
		k = size - i;
		ft_put_char_2(addr + i, fd, k);
		i += 16;
	}
	return (addr);
}
*/
