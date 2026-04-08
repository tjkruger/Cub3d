/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:32:11 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/22 15:02:47 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*s1 == '\0' || *s2 == '\0')
		{
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		if (*s1 != *s2)
		{
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}
