/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:09:24 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/14 17:29:13 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
int	main(void)
{
	char	test1;
	char	test2;

	test1 = '5';
	test2 = 'z';
	printf("Is '%c' alphabetic? %d\n", test1, ft_isdigit(test1));
	printf("Is '%c' alphabetic? %d\n", test2, ft_isdigit(test2));
	for (int i = 0; i < 255; i ++)
	{
		int isalpha = ft_isdigit(
i);
		printf("char: %c, int: %d, is alpha: %d\n", (char)i, i, isalpha);
	}
	return (0);
}
*/