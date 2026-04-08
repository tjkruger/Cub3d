/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:15:06 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/18 17:17:51 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned int	my_len(const char *str)
{
	unsigned int	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int dstsize)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	to_append;
	unsigned int	i;

	dest_len = 0;
	src_len = my_len(src);
	while (dest[dest_len] != '\0' && dest_len < dstsize)
	{
		dest_len++;
	}
	if (dstsize <= dest_len)
	{
		return (dstsize + src_len);
	}
	to_append = dstsize - dest_len - 1;
	i = 0;
	while (i < to_append && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
