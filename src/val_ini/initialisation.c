/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:43:28 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 20:29:50 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_main	*initialise(void)
{
	int		i;
	t_main	*main;

	i = 0;
	main = malloc(sizeof(t_main));
	if (!main)
		return (NULL);
	main->parser = malloc(sizeof(t_parser));
	main->map_data = malloc(sizeof(t_map_data));
	main->player = malloc(sizeof(t_player));
	while (i < 4)
	{
		main->textures[i] = NULL;
		i++;
	}
	return (main);
}

int	is_only_num(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!(s[i] == ' ' || s[i] == ',' || ft_isdigit(s[i])))
			return (0);
		i++;
	}
	return (1);
}

int	store_identifier(char *line, t_map_data *map_data, t_parser *parser)
{
	if (is_identifier(line, "NO"))
		map_data->north_texture = extract_value(line);
	else if (is_identifier(line, "SO"))
		map_data->south_texture = extract_value(line);
	else if (is_identifier(line, "WE"))
		map_data->west_texture = extract_value(line);
	else if (is_identifier(line, "EA"))
		map_data->east_texture = extract_value(line);
	else if (is_identifier(line, "F"))
	{
		parser->floor_color = extract_value(line);
		if (!(is_only_num(parser->floor_color)))
			return (0);
	}
	else if (is_identifier(line, "C"))
	{
		parser->ceiling_color = extract_value(line);
		if (!(is_only_num(parser->ceiling_color)))
			return (0);
	}
	else
		return (0);
	return (1);
}

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

void	get_height_and_length(t_map_data *map)
{
	int	i;
	int	j;
	int	len;
	int	p_counter;

	i = 0;
	j = 0;
	len = 0;
	p_counter = 0;
	while (map->map[i] != NULL)
	{
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'W')
			{
				helper(i, j, p_counter, map);
				p_counter++;
			}
			j++;
		}
		if (j > len)
			len = j;
		j = 0;
		i++;
	}
	map->map_height = i;
	map->map_width = len;
}
