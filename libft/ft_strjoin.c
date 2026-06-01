/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:27:18 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/15 14:31:46 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (dst);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	if ((!s1 || !*s1) && (!s2 || !*s2))
		return (NULL);
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (free(s1), NULL);
	ft_strcpy(str, s1);
	ft_strcpy(str + len1, s2);
	if (!str)
		return (free(s1), NULL);
	str[len1 + len2] = '\0';
	free(s1);
	return (str);
}
