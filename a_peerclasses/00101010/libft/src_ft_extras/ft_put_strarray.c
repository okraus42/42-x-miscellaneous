/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_strarray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:11:53 by okraus            #+#    #+#             */
/*   Updated: 2023/05/09 15:02:52 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	ft_put_strarray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("arr%02i : %s\n", i, arr[i]);
		i++;
	}
}