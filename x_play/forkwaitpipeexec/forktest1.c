/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forktest1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:08:31 by okraus            #+#    #+#             */
/*   Updated: 2023/03/31 16:51:23 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
#include <stdlib.h>
//#include <sys/types.h>
#include <sys/wait.h>
//#include <time.h>
#include "../header/libft.h"

int main(void)
{
    int id;
    int n;
    int i;
    int b;
    int status;

    id = fork();
    i = 1;
    if (id)
    {
        //this is parent, id is of child process
        n = 10;
        b = 0;
        wait(&status);       
    }
    else
    {
        //this is child
        n = 0;
        b = 10;
    }
    while (i <= n + b)
    {
        ft_printf("%i , %i\n", n + i, id);
        i++;
    }
    if (id)
        ft_printf("\n");
    return (0);
}