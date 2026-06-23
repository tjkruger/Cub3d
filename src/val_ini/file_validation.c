/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 20:10:17 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 23:02:06 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_identifier(char *line, char *id)
{
	int	i;

	i = 0;
	while (id[i] && line[i] == id[i])
		i++;
	return (id[i] == '\0' && (line[i] == ' ' || line[i] == '\t'));
}

char	*extract_value(char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	len = 0;
	while (line[i + len] && line[i + len] != '\n')
		len++;
	return (ft_substr(line, i, len));
}

void	exit_texture_error(const char *direction)
{
	write(2, "Error\nTexture not loaded: ", 26);
	write(2, direction, ft_strlen(direction));
	write(2, "\n", 1);
	exit(1);
}

void	validate_single_texture(const char *path, const char *direction)
{
	int	fd;

	if (!path)
		exit_texture_error(direction);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_texture_error(direction);
	close(fd);
}

void	validate_textures(t_map_data *map)
{
	validate_single_texture(map->north_texture, "north");
	validate_single_texture(map->east_texture, "east");
	validate_single_texture(map->south_texture, "south");
	validate_single_texture(map->west_texture, "west");
}
