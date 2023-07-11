/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:36:04 by okraus            #+#    #+#             */
/*   Updated: 2023/05/14 13:45:32 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int	ft_handler3(int i)
{
	if (i == 0)
		return (1);
	if (i == 1)
		return (2);
	if (i == 2)
		return (4);
	if (i == 3)
		return (8);
	if (i == 4)
		return (16);
	if (i == 5)
		return (32);
	if (i == 6)
		return (64);
	return (128);
}

void	ft_handler(int sig)
{
	static unsigned char	c;
	static int				i;
	int						x;

	x = ft_handler3(i);
	if (sig == SIGUSR1)
		c += x;
	else if (sig == SIGUSR2)
		c += 0;
	else
		printf("ERROR: Caugh another signal = %d?!\n", sig);
	i++;
	if (i == 8)
	{
		printf("%c", c);
		c = 0;
		i = 0;
	}
	//printf("received signal: %d", sig);
}

//pid_t is integer

int	main(void)
{
	pid_t	pid;
	//struct	sigaction sig;

	pid = getpid();
	printf("Server pid is: %i\n", pid);
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, ft_handler);
	while(pid)
	{
		
		sleep(1);
		//kill(pid, SIGUSR1);
		//printf("sleeping\n");
	}
	printf("FATAL ERROR\n");
	return (0);
}