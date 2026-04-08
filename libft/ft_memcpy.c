/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:36:45 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/22 14:16:46 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned int	i;
	char			*cdest;
	char			*csrc;

	csrc = (char *)src;
	cdest = (char *)dest;
	if (cdest == NULL && csrc == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "Hello, World!";
	char	dest[50];

	// Using my_memcpy function to copy the string
	my_memcpy(dest, src, sizeof(src));
	printf("Copied string: %s\n", dest);
	return (0);
}
*/