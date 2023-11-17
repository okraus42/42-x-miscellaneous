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

#include "ft_printf.h"
#include <stdio.h>

int	ft_printf(const char *s, ...);

int	main(void)
{
	char			c;
	char			d;
	unsigned int	u;
	int				pf;
	int				fp;
	int				num;
	char			*s = "@@@";
	char			*s2 = NULL;

	c = 'a';
	d = 'b';
	num = 0x7FFFFFFF;
	u = 0xFFFFFFFF;
	// //uncomment for bonus
	// pf = printf("printf : a%pbc%%de%5cfg%-20.15uhij%2sk%-+20.15dlm% inop%#20.15Xq%#xr\n", (void *)&c, d, u, s, num, 0, u, u);
	// fp = ft_printf("ftprint: a%pbc%%de%5cfg%-20.15uhij%2sk%-+20.15dlm% inop%#20.15Xq%#xr\n", (void *)&c, d, u, s, num, 0, u, u);
	// printf ("pf = %d, fp = %d\n", pf, fp);
	// pf = printf("%.3d\n", -1234);
	// fp = ft_printf("%.3d\n", -1234);
	// printf ("pf = %d, fp = %d\n", pf, fp);
	// pf = printf("%-9sScience!\n", "Aperture");
	// fp = ft_printf("%-9sScience!\n", "Aperture");
	// printf ("pf = %d, fp = %d\n", pf, fp);
	// pf = printf("%8p-%8s\n", NULL, s2);
	// fp = ft_printf("%8p-%8s\n", NULL, s2);
	// printf ("pf = %d, fp = %d\n", pf, fp);
	
	pf = printf("%i|%i|%i\n", -2147483647 - 1, 0, 0x7FFFFFFF);
	fp = ft_printf("%i|%i|%i\n", -2147483647 - 1, 0, 0x7FFFFFFF);
	printf ("pf = %d, fp = %d\n", pf, fp);
	pf = printf("%p-%s\n", NULL, s2);
	fp = ft_printf("%p-%s\n", NULL, s2);
	printf ("pf = %d, fp = %d\n", pf, fp);
	pf = printf("printf : a%pbc%%de%cfg%uhij%sk%dlm%inop%Xq%xr\n", (void *)&c, d, u, s, num, 0, u, u);
	fp = ft_printf("ftprint: a%pbc%%de%cfg%uhij%sk%dlm%inop%Xq%xr\n", (void *)&c, d, u, s, num, 0, u, u);
	printf ("pf = %d, fp = %d\n", pf, fp);
	return (0);
}
