/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:07:23 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/14 20:34:39 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int dstsize)
{
	unsigned int	src_len;

	src_len = 0;
	if (dstsize > 0)
	{
		while (src[src_len] != '\0' && src_len < dstsize - 1)
		{
			dest[src_len] = src[src_len];
			src_len++;
		}
		dest[src_len] = '\0';
	}
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	return (src_len);
}
