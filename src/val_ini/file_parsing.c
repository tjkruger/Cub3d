/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:03:40 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 22:19:31 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	read_map_lines(char *line, t_map_data *map_data, int fd)
{
	int	send_line;

	send_line = make_map(line, map_data);
	while (send_line && line)
	{
		free(line);
		line = get_next_line(fd);
		send_line = make_map(line, map_data);
	}
	free(line);
	get_height_and_length(map_data);
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
	read_map_lines(line, main->map_data, main->parser->map_fd);
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
