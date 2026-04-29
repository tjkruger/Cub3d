/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:00:18 by tjkruger          #+#    #+#             */
/*   Updated: 2024/12/09 17:33:26 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
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
	if (!new_str)
		return (NULL);
	while (count < len)
	{
		new_str[count] = s1[count];
		count++;
	}
	new_str[len] = '\0';
	free(s1);
	return (new_str);
}
