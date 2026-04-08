/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:47:53 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/14 17:30:43 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

/*
int	main(void)
{
	char	test1[] = "Hello, world!";
	char	test2[] = "";
	char	test3[] = "OpenAI";
	char	test4[50] = "Mutable array";
	char	*test5;

	test5 = "This is a string literal.";
	printf("Length of '%s': %d\n", test1, ft_strlen(test1));
	printf("Length of '%s': %d\n", test2, ft_strlen(test2));
	printf("Length of '%s': %d\n", test3, ft_strlen(test3));
	printf("Length of '%s': %d\n", test4, ft_strlen(test4));
	printf("Length of '%s': %d\n", test5, ft_strlen(test5));
	return (0);
}
*/