/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:11:39 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/21 16:32:09 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	get_len(int n)
{
	int	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n != 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int		lengh;
	char	*result;
	int		is_neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	lengh = get_len(n);
	result = (char *)malloc((lengh + 1) * sizeof(char));
	if (!result)
		return (NULL);
	is_neg = (n < 0);
	if (is_neg)
		n = -n;
	result[lengh] = '\0';
	while (lengh > 0)
	{
		lengh--;
		result[lengh] = (n % 10) + '0';
		n /= 10;
	}
	if (is_neg)
		result[0] = '-';
	return (result);
}
