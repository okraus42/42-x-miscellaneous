/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ok_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:50:17 by okraus            #+#    #+#             */
/*   Updated: 2023/12/03 16:18:50 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/header/libft.h"

static void	ok_get_arr_size(char **file, int *height, int *width)
{
	int	i;
	int	j;

	j = 0;
	while (file[j])
	{
		while(file[j][i])
			++i;
		if (i > *width)
			*width = i;
		++j;
	}
	height = j;
}

char	**ok_readfile(int fd, int *height, int *width)
{
	char	**arr;
	char	**file;
	char	*buff;
	int		r;
	int		s;

	*height = 0;
	*width = 0;
	s = 1000000;
	buff = malloc(s);
	if (!buff)
		return (NULL);
	r = read(fd, buff, s);
	if (r == s || r <=0)
		return(NULL);
	file = ft_split(buff, '\n');
	ok_get_arr_size(file, height, width);
	arr = malloc(sizeof(char *) * (*height + 3));
	if (!arr)
		return (NULL);
	//zeroes
	//zero-text-zero
	//zeroes
}