/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 22:01:35 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 22:19:51 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_split(char **s, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	validate_color_values(char **s)
{
	if (!s[2] || s[3])
		return (0);
	if (ft_atoi(s[0]) < 0 || ft_atoi(s[0]) > 255)
		return (0);
	if (ft_atoi(s[1]) < 0 || ft_atoi(s[1]) > 255)
		return (0);
	if (ft_atoi(s[2]) < 0 || ft_atoi(s[2]) > 255)
		return (0);
	return (1);
}

static int	parse_single_color(char *color_str)
{
	char	**s;
	int		result;

	s = ft_split(color_str, ',');
	if (!validate_color_values(s))
	{
		free_split(s, 3);
		return (-1);
	}
	result = (ft_atoi(s[0]) << 16) | (ft_atoi(s[1]) << 8) | ft_atoi(s[2]);
	free_split(s, 3);
	return (result);
}

void	parse_colours(t_map_data *map, t_parser *parser)
{
	map->ceiling_color = parse_single_color(parser->ceiling_color);
	if (map->ceiling_color == -1)
	{
		write(2, "Error\nInvalid ceiling color\n", 27);
		exit(1);
	}
	map->floor_color = parse_single_color(parser->floor_color);
	if (map->floor_color == -1)
	{
		write(2, "Error\nInvalid floor color\n", 25);
		exit(1);
	}
}
