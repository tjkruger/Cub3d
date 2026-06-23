/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 21:58:32 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 23:11:56 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '1' || line[i] == '0');
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S' || c == 'W'
		|| c == ' ' || c == '\n' || c == '\t');
}

int	line_is_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_valid_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	make_map(char *l, t_map_data *map)
{
	char	*all;

	all = NULL;
	if (!l)
	{
		map->map = ft_split(all, '\n');
		free(all);
		return (0);
	}
	if (line_is_valid(l))
		all = ft_strjoin(all, l);
	else
	{
		map->map = ft_split(all, '\n');
		free(all);
		return (0);
	}
	return (1);
}
