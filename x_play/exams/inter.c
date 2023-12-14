/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:47:44 by okraus            #+#    #+#             */
/*   Updated: 2023/12/14 17:56:30 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	cc -Wall -Wextra -Werror inter.c -o inter

// Assignment name  : inter
// Expected files   : inter.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that takes two strings and displays, without doubles, the
// characters that appear in both strings, in the order they appear in the first
// one.

// The display will be followed by a \n.

// If the number of arguments is not 2, the program displays \n.

// Examples:

// $>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
// padinto$
// $>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
// df6ewg4$
// $>./inter "rien" "cette phrase ne cache rien" | cat -e
// rien$
// $>./inter | cat -e
// $

#include <unistd.h>

int	main(int argc, char *argv[])
{
	int						i;
	unsigned char			*s1;
	unsigned char			*s2;
	static unsigned char	s1a[256];
	static unsigned char	s2a[256];

	i = 0;
	if (argc == 3)
	{
		s1 = (unsigned char *)argv[1];
		s2 = (unsigned char *)argv[2];
		while (s2[i])
		{
			s2a[s2[i]] = 1;
			++i;
		}
		i = 0;
		while (s1[i])
		{
			if (!s1a[s1[i]] && s2a[s1[i]])
			{
				s1a[s1[i]] = 1;
				write(1, &s1[i], 1);
			}
			++i;
		}
	}
	write(1, "\n", 1);
	return (0);
}
