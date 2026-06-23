/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:03:40 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 20:32:41 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static int	parse_single_color(const char *color_str)
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

static void	read_headers(t_main *main, int *headers_found)
{
	char	*line;

	line = get_next_line(main->parser->map_fd);
	while (line && is_map_line(line) == 0)
	{
		if (line[0] != '\n')
			*headers_found += store_identifier(line, main->map_data,
					main->parser);
		free(line);
		line = get_next_line(main->parser->map_fd);
	}
	if (*headers_found < 6)
	{
		free(line);
		write(2, "Error\nMissing or invalid identifiers in map file\n", 49);
		exit(1);
	}
	read_map_lines(line, main->map_data);
}

static void	read_map_lines(char *line, t_map_data *map_data)
{
	int	send_line;

	send_line = make_map(line, map_data);
	while (send_line && line)
	{
		free(line);
		line = get_next_line(/* fd */);
		send_line = make_map(line, map_data);
	}
	free(line);
	get_height_and_length(map_data);
}

void	copy_file_blindly(t_main *main)
{
	int	headers_found;

	headers_found = 0;
	read_headers(main, &headers_found);
}

void	parse(int ac, char **av, t_main *main)
{
	check_args(ac, av, main->parser);
	copy_file_blindly(main);
	validate_textures(main->map_data);
	parse_colours(main->map_data, main->parser);
	validate_map(main->map_data);
}
