/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pritnf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:51:02 by okraus            #+#    #+#             */
/*   Updated: 2023/10/14 13:31:07 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/libft.h"

int	main(void)
{
	//ft_printf("abc%2s%cab%#012.5ic%%def", "xxx", 'c', 0x12345678);
	write(1, "\n", 1);

	ft_printf("123%ca%+05ib%+020.15ic%2.4sd%9.6se%-8.2sfghijkl%%\n", 'c', -1234, -0x12345678, "abcdef", (char *)NULL, "abcdef");
	printf("123%ca%+05ib%+020.15ic%2.4sd%9.6se%-8.2sfghijkl%%\n", 'c', -1234, -0x12345678, "abcdef", (char *)NULL, "abcdef");
	ft_printf("a%ob%uc%xd%Xe%lxf%#og%10xh%10.5xijkl\n", 42, 42, 42, 42, 9223372036854775808UL, 42, 42, 42);
	printf("a%ob%uc%xd%Xe%lxf%#og%10xh%10.5xijkl\n", 42, 42, 42, 42, 9223372036854775808UL, 42, 42, 42);
	
	ft_printf("%30p %*p %*.*i\n", NULL, 20, &"abcdef", 16, 4, 42);
	printf("%30p %*p %*.*i\n", NULL, 20, &"abcdef", 16, 4, 42);

	ft_printf("%30p %*p %#*.*^*B\n", NULL, 20, &"abcdef", 16, 8, 2, 42);
	ft_printf("%30p %*p %#*.*B\n", NULL, 20, &"abcdef", 16, 8, 42);
	int i = 0;
	while (i++ < 42)
		ft_printf("%30p %*p %#*.*^*B\n", NULL, 20, &"abcdef", 16, 8, i + 1, i);

	//printf("%lli %s %s\n", -9223372036854775807LL -1LL, ft_ltoa_base(-9223372036854775807LL -1LL, "0123456789abcdef", 10), ft_ultoa_base(0x1234567890fDECBA, "0123456789abcdef", 16));
	printf("Color \033[1;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[2;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[3;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[4;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[5;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[6;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[7;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[8;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[9;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[20;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[21;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[28;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[51;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[52;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[53;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[64;38;2;255;63;127;48;2;63;195;31mtest\033[0m\n");
	printf("Color \033[2mtest\033[0m\n");
	printf("Color test\n");
	ft_printf("FTPRINTF: Color %31.*^*Ctest%C\n", 0xFF0000, 0XFF00);
	ft_printf("FTPRINTF: Color %31.*^*C%20.14^24LB%C\n", 0xFF0000, 0XFF00, 0xffffffffffULL);
	return (0);
}
