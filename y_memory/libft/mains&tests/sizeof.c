/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:49:23 by okraus            #+#    #+#             */
/*   Updated: 2023/03/02 15:21:49 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	main(void)
{
	static char c = '\0';

	printf("asize of:\nNULL = %i, 0 = %i, '\\0' = %i, \"\" = %i, c = %i\n",
		(int)sizeof(NULL), (int)sizeof(0), (int)sizeof('\0'), (int)sizeof(""), (int)sizeof(c));
	ft_printf("bsize of:\nNULL = %i, 0 = %i, '\\0' = %i, \"\" = %i, c = %i\n",
		sizeof(NULL), sizeof(0), sizeof('\0'), sizeof(""), sizeof(c));
	return (0);
}
