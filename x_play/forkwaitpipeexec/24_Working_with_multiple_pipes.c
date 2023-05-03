/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_Working_with_multiple_pipes.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:18:50 by okraus            #+#    #+#             */
/*   Updated: 2023/05/03 17:43:15 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int	fd[3][2];
	int	i;
	int	x;
	int	pid[3];

	pid[0] = 0; //pid[0] for parent and organisation;
	i = 0;
	while (i < 3)
	{
		if (pipe(fd[i]) < 0)
		{
			//normally should close opened pipes before returning an error
			return (1);
		}
		i++;
	}
	pid[1] = fork();
	if (pid[1] < 0)
	{
		return (2);
	}
	//child process 1
	if (pid[1] == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		if (read(fd[0][0], &x, sizeof(int)) < 0)
		{
			return (3);
		}
		x += 5;
		if (write(fd[1][1], &x, sizeof(int)) < 0)
		{
			return (4);
		}
		close(fd[0][0]);
		close(fd[1][1]);
		return (0);
	}
	pid[2] = fork();
	if (pid[2] < 0)
	{
		return (5);
	}
	//child process 2
	if (pid[2] == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		if (read(fd[1][0], &x, sizeof(int)) < 0)
		{
			return (6);
		}
		x += 5;
		if (write(fd[2][1], &x, sizeof(int)) < 0)
		{
			return (7);
		}
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}
	//Parent process
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	printf("Input number: ");
	scanf("%d", &x);
	if (write(fd[0][1], &x, sizeof(int)) < 0)
	{
		return (8);
	}
	close(fd[0][1]);
	if (read(fd[2][0], &x, sizeof(int)) < 0)
	{
		return (9);
	}
	close(fd[2][0]);
	printf("Result is %d\n", x);
	waitpid(pid[1], NULL, 0);
	waitpid(pid[2], NULL, 0);
	return (0);
}
