/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:54:04 by okraus            #+#    #+#             */
/*   Updated: 2023/05/14 13:14:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>


void	ft_send_bit(int pid, unsigned char c)
{
	if (c)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100);
}

void	ft_send_char(int pid, unsigned char c)
{
	ft_send_bit(pid, c & 1);
	ft_send_bit(pid, c & 2);
	ft_send_bit(pid, c & 4);
	ft_send_bit(pid, c & 8);
	ft_send_bit(pid, c & 16);
	ft_send_bit(pid, c & 32);
	ft_send_bit(pid, c & 64);
	ft_send_bit(pid, c & 128);
}


// void	ft_handler(int sig)
// {
// 	if (sig == SIGUSR1)
// 		printf("caugh SIGUSR1 signal = %d\n", sig);
// 	else if (sig == SIGUSR2)
// 		printf("caugh SIGUSR2 signal = %d\n", sig);
// 	else
// 		printf("caugh another signal = %d?!\n", sig);
// }

//pid_t is integer

int	ft_atoi(const char *nptr)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == '\t'
		|| nptr[i] == '\f' || nptr[i] == '\v' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * res);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	pid;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (pid && argv[2][i])
		{
			ft_send_char(pid, argv[2][i]);
			i++;
		}
		ft_send_char(pid, '\n');
	}
	else
	{
		printf("FATAL ERROR\n");
		return (1);
	}
	return (0);
}