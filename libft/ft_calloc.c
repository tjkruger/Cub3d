/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:21:39 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/15 14:30:46 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(int num, int size)
{
	void			*ptr;
	unsigned char	*clear;
	int				i;

	i = 0;
	ptr = malloc(num * size);
	if (!ptr)
		return (0);
	clear = ptr;
	while (i < num * size)
	{
		clear[i] = 0;
		i++;
	}
	return (ptr);
}
