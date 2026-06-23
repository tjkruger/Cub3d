/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player_dimesion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 22:10:36 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 22:11:22 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	helper(int i, int j, int p_counter, t_map_data *map)
{
	if (p_counter > 0)
	{
		write(1, "multiple player pos", 19);
		exit(1);
	}
	map->player_orientation = map->map[i][j];
	map->player_pos.x = j;
	map->player_pos.y = i;
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

static int	get_row_length(char *row)
{
	int	j;

	j = 0;
	while (row[j] != '\0')
		j++;
	return (j);
}

static void	process_row(t_map_data *map, int i, int *p_counter)
{
	int	j;

	j = 0;
	while (map->map[i][j] != '\0')
	{
		if (is_player_char(map->map[i][j]))
		{
			helper(i, j, *p_counter, map);
			(*p_counter)++;
		}
		j++;
	}
}

void	get_height_and_length(t_map_data *map)
{
	int	i;
	int	p_counter;
	int	row_len;

	i = 0;
	p_counter = 0;
	map->map_width = 0;
	while (map->map[i] != NULL)
	{
		process_row(map, i, &p_counter);
		row_len = get_row_length(map->map[i]);
		if (row_len > map->map_width)
			map->map_width = row_len;
		i++;
	}
	map->map_height = i;
}
