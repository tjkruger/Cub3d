/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:57:07 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/22 14:13:39 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, int n)
{
	const unsigned char	*src;
	const unsigned char	*dest;
	int					i;

	src = s1;
	dest = s2;
	if (dest == NULL && src == NULL)
		return (0);
	if (n <= 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (src[i] != dest[i])
		{
			return (src[i] - dest[i]);
		}
		i++;
	}
	return (0);
}
