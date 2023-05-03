/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26_Calling_fork_multiple_times_p2.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:58:29 by okraus            #+#    #+#             */
/*   Updated: 2023/05/03 19:14:19 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define	PROCESS_NUM 10

// n processes, n + 1 pipes
int	main(int argc, char *argv[])
{
	int	pids[PROCESS_NUM];
	int	pipes[PROCESS_NUM + 1][2];
	int	i;
	int	j;
	int x;
	int	y;

	i = 0;
	while (i < PROCESS_NUM +1)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Error with creating pipe\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < PROCESS_NUM)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Error with creating process\n");
			return (2);
		}
		// Child process
		// each process reads from i and writes to i + 1;
		if (pids[i] == 0)
		{
			//close unnecessary pipes
			j = 0;
			while (j < PROCESS_NUM + 1)
			{
				if (j != i)
				{
					close(pipes[j][0]);
				}
				if (j != i + 1)
				{
					close(pipes[j][1]);
				}
				j++;
			}
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
			{
				printf("Error at reading\n");
				return (3);
			}
			printf("(%d) got %d\n", i, x);
			close(pipes[i][0]);
			x++;
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
			{
				printf("Error at writing\n");
				return (4);
			}
			printf("(%d) sent %d\n", i, x);
			close(pipes[i + 1][1]);
			//break; alternative to return 0, terminates the loop.
			return (0);
		}
		i++;
	}
	// MAIN PROCESS
	j = 0;
	while (j < PROCESS_NUM + 1)
	{
		if (j != PROCESS_NUM)
		{
			close(pipes[j][0]);
		}
		if (j != 0)
		{
			close(pipes[j][1]);
		}
		j++;
	}
	y = 5;
	printf("The main process sent %d\n", y);
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
	{
		printf("Error at writing\n");
		return (5);
	}
	close(pipes[0][1]);
	if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1)
	{
		printf("Error at reading\n");
		return (6);
	}
	close(pipes[PROCESS_NUM][0]);
	printf("The final result is %d\n", y);
	while (i < PROCESS_NUM)
	{
		wait(NULL);
		i++;
	}

	return (0);
}
