/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:09:24 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/14 17:29:21 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/*
int	main(void)
{
	char	test1;
	char	test2;

	test1 = 'A';
	test2 = 'z';
	printf("Is '%c' alphabetic? %d\n", test1, ft_isalpha(test1));
	printf("Is '%c' alphabetic? %d\n", test2, ft_isalpha(test2));
	return (0);
}
*/