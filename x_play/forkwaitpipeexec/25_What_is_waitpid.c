/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_What_is_waitpid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:44:54 by okraus            #+#    #+#             */
/*   Updated: 2023/05/03 17:58:22 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int	pid1;
	int	pid2;
	int	pid1_res;
	int	pid2_res;

	pid1 = fork();
	if (pid1 < 0)
	{
		printf("Error creating process\n");
		return (1);
	}
	if (pid1 == 0)
	{
		sleep(4);
		printf("Finished execution (%d)\n", getpid());
		return (0);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		printf("Error creating process\n");
		return (2);
	}
	if (pid2 == 0)
	{
		sleep(1);
		printf("Finished execution (%d)\n", getpid());
		return (0);
	}
	pid1_res = waitpid(pid1, NULL, 0);
	//pid1_res = waitpid(pid1, NULL, WNOHANG);
	//with WNOHANG instead of the 0 saves the status in NULL and does not wait
	printf("Waited for process(%d)\n", pid1_res);
	pid2_res = waitpid(pid2, NULL, 0);
	printf("Waited for process(%d)\n", pid2_res);
	return (0);
}
