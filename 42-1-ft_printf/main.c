/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:49:23 by okraus            #+#    #+#             */
/*   Updated: 2023/01/31 17:17:50 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	num = 2147483647;
	u = 4294967294;
	pf = printf("printf : a%pbc%%de%5cfg%-20.15uhij%2sk%-+20.15dlm% inop%#20.15Xq%xr\n", (void *)&c, d, u, s, num, 0, u, u);
	fp = ft_printf("ftprint: a%pbc%%de%5cfg%-20.15uhij%2sk%-+20.15dlm% inop%#20.15Xq%xr\n", (void *)&c, d, u, s, num, 0, u, u);
	printf ("pf = %d, fp = %d\n", pf, fp);
	pf = printf("%.3d\n", -1234);
	fp = ft_printf("%.3d\n", -1234);
	printf ("pf = %d, fp = %d\n", pf, fp);
	pf = printf("%-9sScience!\n", "Aperture");
	fp = ft_printf("%-9sScience!\n", "Aperture");
	printf ("pf = %d, fp = %d\n", pf, fp);
	pf = printf("%8p-%8s\n", NULL, s2);
	fp = ft_printf("%8p-%8s\n", NULL, s2);
	printf ("pf = %d, fp = %d\n", pf, fp);
	ft_printf("%#+10.4B\n", num);
	return (0);
}
