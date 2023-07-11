/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:19:07 by okraus            #+#    #+#             */
/*   Updated: 2023/05/07 16:10:01 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int	main(int argc, char *argv[])
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	fdi;
	int	fdo;

	fdi = open("input", O_RDONLY);
	fdo = open("output", O_CREAT | O_RDWR | O_TRUNC, 0644);
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
		write(1, "abc\n", 4);
		dup2(fdi, STDIN_FILENO); //STDIN_FILENO = 0;
		write(1, "abc\n", 4);
		dup2(fd[1], STDOUT_FILENO); // STDOUT_FILENO = 1;
		write(1, "abc\n", 4);
		close(fd[0]);
		close(fd[1]);
		write(1, "abc\n", 4);
		execlp("cat", "cat", NULL);
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
		write(1, "123\n", 4);
		dup2(fd[0], STDIN_FILENO); //STDIN_FILENO = 0;
		write(1, "123\n", 4);
		dup2(fdo, STDOUT_FILENO); // STDOUT_FILENO = 1;
		write(1, "123\n", 4);
		close(fd[0]);
		close(fd[1]);
		write(1, "123\n", 4);
		execlp("wc", "wc", "-l", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
