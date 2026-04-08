/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:23:59 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/14 17:29:25 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, int len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (len-- > 0)
	{
		*ptr++ = 0;
	}
}

/*
int	main(void) {

	int array[5];

	bzero(array, sizeof(array));
	printf("Contents of the array after bzero:\n");

	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
	{
		printf("array[%d] = %d\n", i, array[i]);
	}

	return (0);
}
*/
