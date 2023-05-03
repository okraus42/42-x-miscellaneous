/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_Simulating_the_pipe_operator_in_C.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:52:10 by okraus            #+#    #+#             */
/*   Updated: 2023/05/03 15:59:57 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd[2];
    int pid1;

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
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }

    //no need for else because child replaces by exec

    waitpid(pid1, NULL, 0);
    

    return (0);
}
