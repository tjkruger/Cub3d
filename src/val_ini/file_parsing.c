/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:03:40 by tjkruger          #+#    #+#             */
/*   Updated: 2026/04/25 17:04:19 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_colours(t_map_data *map, t_parser *parser)
{
	char **s;
	s = ft_split(parser->ceiling_color, ',');
	if(s[2] && !s[3] && ft_atoi(s[0]) >= 0 && ft_atoi(s[0]) <= 255 && ft_atoi(s[1]) >= 0 && ft_atoi(s[1]) <= 255 && ft_atoi(s[2]) >= 0 && ft_atoi(s[2]) <= 255)
		map->ceiling_color = (atoi(s[0]) << 16) | (atoi(s[1]) << 8) | atoi(s[2]);
	else
	{
		write(1, "error in ceiling colour parsing", 31);
		exit(1);
	}
	free(s[0]);
	free(s[1]);
	free(s[2]);
	free(s);
	s = ft_split(parser->floor_color, ',');
	if(s[2] && !s[3] && ft_atoi(s[0]) >= 0 && ft_atoi(s[0]) <= 255 && ft_atoi(s[1]) >= 0 && ft_atoi(s[1]) <= 255 && ft_atoi(s[2]) >= 0 && ft_atoi(s[2]) <= 255)
		map->floor_color = (atoi(s[0]) << 16) | (atoi(s[1]) << 8) | atoi(s[2]);
	else
	{
		write(1, "error in floor colour parsing", 29);
		exit(1);
	}
	free(s[0]);
	free(s[1]);
	free(s[2]);
	free(s);
}

void	copy_file_blindly(t_main *main)
{
	char	*line;
	int		headers_found;
	int		send_line;

	headers_found = 0;
	line = get_next_line(main->parser->map_fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(main->parser->map_fd);
			continue ;
		}
		if (!is_map_line(line))
			headers_found += store_identifier(line, main->map_data, main->parser);
		else
			break ;
		free(line);
		line = get_next_line(main->parser->map_fd);
	}
	if (headers_found < 6)
	{
		write(2, "Error\nMissing or invalid identifiers in map file\n", 49);
		exit(1);
	}
	send_line = make_map(line, main->map_data);
	while (send_line && line)
	{
		free(line);
		line = get_next_line(main->parser->map_fd);
		send_line = make_map(line, main->map_data);
	}
	free(line);
	get_height_and_length(main->map_data);
}

void	parse(int ac, char **av, t_main *main)
{
	check_args(ac, av, main->parser);
	copy_file_blindly(main);
	validate_textures(main->map_data);
	parse_colours(main->map_data, main->parser);
    validate_map(main->map_data);
}