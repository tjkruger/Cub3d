/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:11:07 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/22 14:41:18 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strnstr(const char *mstr, const char *sstr, int len)
{
	int	j;
	int	i;

	i = 0;
	if (!*sstr)
		return ((char *)mstr);
	while (mstr[i] && (len < 0 || i < len))
	{
		j = 0;
		while (sstr[j] && mstr[i + j] == sstr[j] && (len < 0 || (i + j) < len))
			j++;
		if (!sstr[j])
			return ((char *)&mstr[i]);
		i++;
	}
	return (0);
}
