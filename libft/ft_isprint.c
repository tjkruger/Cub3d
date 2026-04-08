/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:40:16 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/14 17:29:11 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*
int	main(void)
{
	int	isprint;

	for (int i = 0; i < 255; i ++)
	{
		isprint = ft_isprint(i);
		printf("char: %c, int: %d, is alnum: %d\n", (char)i, i, isprint);
	}
	return (0);
}
*/