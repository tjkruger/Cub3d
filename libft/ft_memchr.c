/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:42:53 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/15 16:08:53 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, int n)
{
	unsigned char		target;
	const unsigned char	*ptr;
	int					i;

	i = 0;
	ptr = s;
	target = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == target)
		{
			return ((void *)&ptr[i]);
		}
		i++;
	}
	return (0);
}
