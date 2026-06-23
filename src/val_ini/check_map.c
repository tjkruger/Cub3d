/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:47:01 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 21:59:58 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_map_copy(char **copy)
{
	int	y;

	y = 0;
	while (copy[y])
		free(copy[y++]);
	free(copy);
}

void	validate_map(t_map_data *map_data)
{
	t_flood	f;

	f.map = make_map_copy(map_data->map, map_data->map_height);
	f.width = map_data->map_width;
	f.height = map_data->map_height;
	floodfill(&f, map_data->player_pos.x, map_data->player_pos.y);
	free_map_copy(f.map);
}

char	**make_map_copy(char **map, int height)
{
	char	**copy;
	int		i;
	int		j;

	copy = malloc(sizeof(char *) * (height + 1));
	i = 0;
	while (i < height)
	{
		j = 0;
		copy[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		while (map[i][j] != '\0')
		{
			copy[i][j] = map[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
