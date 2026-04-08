/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:12:40 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/14 17:29:15 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*
int	main(void)
{
	int	isascii;

	for (int i = 0; i < 255; i ++)
	{
		isascii = ft_isascii(i);
		printf("char: %c, int: %d, is alnum: %d\n", (char)i, i, isascii);
	}
	return (0);
}
*/