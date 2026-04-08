/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:54:06 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/22 14:14:50 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	copy_backward(char *dest, const char *src, unsigned int n)
{
	dest += n - 1;
	src += n - 1;
	while (n--)
	{
		*dest-- = *src--;
	}
}

void	copy_forward(char *dest, const char *src, unsigned int n)
{
	while (n--)
	{
		*dest++ = *src++;
	}
}

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	if (s < d && (s + n) > d)
	{
		copy_backward(d, s, n);
	}
	else
	{
		copy_forward(d, s, n);
	}
	return (dest);
}
