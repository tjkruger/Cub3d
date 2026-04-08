/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:20:55 by tjkruger          #+#    #+#             */
/*   Updated: 2024/10/28 14:24:51 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_end;

	if (*lst == NULL)
		*lst = new;
	else
	{
		lst_end = ft_lstlast(*lst);
		lst_end->next = new;
	}
}
