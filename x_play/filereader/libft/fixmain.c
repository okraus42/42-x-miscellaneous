/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:49:23 by okraus            #+#    #+#             */
/*   Updated: 2023/11/17 18:52:16 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/libft.h"
#include <stdio.h>

int	ft_printf(const char *s, ...);

int	main(int ac, char *av[])
{
	int	fp;
	
	fp = ft_printf("ftprint: <32.0>   %^*P\n\n", 1, 64);
	fp = ft_printf("ftprint: <16.00>  %^*P\n\n", 2, 64);
	fp = ft_printf("ftprint: <8.000 > %^*P\n\n", 3, 64);
	fp = ft_printf("ftprint: < 4.0000>%^*P\n\n", 4, 64);
	ft_printf("\n\n");
	fp = ft_printf("ftprint: <32.00> %.*^*P\n\n", 2, 1, 64);
	fp = ft_printf("ftprint: <16.00> %.*^*P\n\n", 2, 2, 64);
	fp = ft_printf("ftprint: < 8.00> %.*^*P\n\n", 2, 3, 64);
	fp = ft_printf("ftprint: < 4.00> %.*^*P\n\n", 2, 4, 64);
	fp = ft_printf("ftprint: <32.0>  %.*^*P\n\n", 1, 1, 64);
	fp = ft_printf("ftprint: <16.0>  %.*^*P\n\n", 1, 2, 64);
	fp = ft_printf("ftprint: < 8.0>  %.*^*P\n\n", 1, 3, 64);
	fp = ft_printf("ftprint: < 4.0>  %.*^*P\n\n", 1, 4, 64);
	fp = ft_printf("ftprint: <32>   %.*^*P\n\n", 0, 1, 64);
	fp = ft_printf("ftprint: <16>   %.*^*P\n\n", 0, 2, 64);
	fp = ft_printf("ftprint: < 8>   %.*^*P\n\n", 0, 3, 64);
	fp = ft_printf("ftprint: < 4>   %.*^*P\n\n", 0, 4, 64);
	if (ac < 4)
		return (1);
	fp = ft_printf("ftprint: %.*^*P\n\n", ft_atoi(av[1]), ft_atoi(av[2]), ft_atoi(av[3]));
	printf ("fp = %d\n", fp);
	return (0);
}

// a 1 8 2559
