/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_Simulating_the_pipe_operator_in_C.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:19:07 by okraus            #+#    #+#             */
/*   Updated: 2023/05/03 16:19:28 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
	{
		return (1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		return (2);
	}
	//Child process 1 (ping)
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO); // STDOUT_FILENO = 1;
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	//no need for else because child replaces by exec
	pid2 = fork();
	if (pid2 < 0)
	{
		return (3);
	}
	//Child process 2 (grep)
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO); //STDIN_FILENO = 0;
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
