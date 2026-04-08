/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:11:24 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/22 16:02:36 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *str, int c)
{
	const char	*last_occurrence;
	char		ch;

	last_occurrence = NULL;
	ch = (char)c;
	while (*str)
	{
		if (*str == ch)
		{
			last_occurrence = str;
		}
		str++;
	}
	if (ch == '\0')
	{
		return ((char *)str);
	}
	return ((char *)last_occurrence);
}
