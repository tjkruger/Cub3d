/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:00:45 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/14 20:09:14 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z'));
}

/*
int	main(void)
{
	int	isalnum;

	for (int i = 0; i < 255; i ++)
	{
		isalnum = ft_isalnum(i);
		printf("char: %c, int: %d, is alnum: %d\n", (char)i, i, isalnum);
	}
	return (0);
}
*/