/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:49:23 by okraus            #+#    #+#             */
/*   Updated: 2023/06/24 16:46:21 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/libft.h"
#include <stdio.h>

int	ft_printf(const char *s, ...);

int	main(void)
{
	int	fp;
	
	fp = ft_printf("ftprint: %.2^8P\n", 255);
	printf ("fp = %d\n", fp);
	return (0);
}
