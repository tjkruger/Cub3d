/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:12:04 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/21 15:41:44 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	check_conditions(const char *s, unsigned int start, size_t *s_len)
{
	while (s[*s_len] != '\0')
		(*s_len)++;
	if (start >= (*s_len))
		return (false);
	return (true);
}

static char	*allocate_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	bool	worked;
	size_t	s_len;

	s_len = 0;
	if (!s)
		return (NULL);
	worked = check_conditions(s, start, &s_len);
	if (worked == false)
		return (ft_calloc(1, sizeof(char *)));
	if (start + len > s_len)
		len = s_len - start;
	return (allocate_substr(s, start, len));
}

/*
int	main(void)
{
	char	str[] = "lorem ipsum dolor sit amet";

	printf("1: |%s|\n", ft_substr(str, 0, 10));
	printf("1: |%s|\n", ft_substr(str, 7, 10));
	printf("1: |%s|\n", ft_substr(str, 7, 0));
}
*/