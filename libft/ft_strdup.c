/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:45:36 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/17 13:15:20 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		len;
	int		count;
	char	*new_str;

	len = 0;
	count = 0;
	while (s1[len] != '\0')
	{
		len++;
	}
	new_str = (char *)malloc(len + 1);
	if (new_str == 0)
	{
		return (0);
	}
	while (count < len)
	{
		new_str[count] = s1[count];
		count++;
	}
	new_str[len] = '\0';
	return (new_str);
}
