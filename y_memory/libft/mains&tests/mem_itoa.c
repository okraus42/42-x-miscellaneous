/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:57:42 by okraus            #+#    #+#             */
/*   Updated: 2023/01/22 12:59:28 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//void	*ft_print_memory_plus2(void *addr, int fd, size_t size, size_t pd);

char	*mem_itoa(int n)
{
	int			i;
	char		*number;
	static void	*p;

	i = 0;
	//number = (char *)ft_evil_calloc_plus(1, 9, 32);
	number = (char *)ft_calloc(1, 9);
	p = (void *)number;
	ft_printf("pass %i, %p\n", i, p);
	i++;
	ft_print_memory_plus2(p, 1, 0, 48);
	if (n >= 0 && number)
	{
		*--number = '0' + (n % 10);
		ft_printf("pass %i\n | a", i);
		i++;
		ft_print_memory_plus2(p, 1, 0, 48);
		n /= 10;
		while (n != 0)
		{
			*--number = '0' + n % 10;
			ft_printf("pass %i\n | b", i);
			i++;
			ft_print_memory_plus2(p, 1, 0, 48);
			n /= 10;
		}
	}
	else if (number)
	{
		*--number = '0' - (n % 10);
		ft_printf("pass %i | c\n", i);
		i++;
		ft_print_memory_plus2(p, 1, 0, 48);
		n /= 10;
		while (n != 0)
		{
			*--number = '0' - (n % 10);
			ft_printf("pass %i | d\n", i);
			i++;
			ft_print_memory_plus2(p, 1, 0, 48);
			n /= 10;
		}
		*--number = '-';
		ft_printf("pass %i | e\n", i);
		i++;
		ft_print_memory_plus2(p, 1, 0, 48);
	}
	return (ft_strdup(number));
}

int	main(void)
{
	int		n;
	char	*s;

	n = -2147483648;
	s = mem_itoa(n);
	ft_printf("finished, s = %s\n", s);
	ft_print_memory_plus2((void *)s, 1, 0, 160);
	return (0);
}
