#include "../../include/cub3d.h"

void	check_extension(char *path)
{
	int	len;

	len = 0;
	while (path[len])
		len++;
	if (len < 5 || path[len - 4] != '.' || path[len - 3] != 'c'
		|| path[len - 2] != 'u' || path[len - 1] != 'b')
	{
		write(2, "Error\nInvalid file extension, expected .cub\n", 44);
		exit(1);
	}
}

//check the input for mistakes
void	check_args(int ac, char **av, t_parser *parser)
{
	if (ac != 2)
	{
		write(2, "Error\nUsage: ./cub3d <map.cub>\n", 31);
		exit(1);
	}
	check_extension(av[1]);
	parser->map_fd = open(av[1], O_RDONLY);
	if (parser->map_fd < 0)
	{
		write(2, "Error\nCould not open map file\n", 30);
		exit(1);
	}
	parser->map_path = av[1];
}

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

void	validate_textures(t_map_data *map)
{
	int i = 0;
	if(!map->north_texture || (i = open(map->north_texture,O_RDONLY)) < 0)
	{
		write(1, "north texture wasnt loaded", 26);
		exit(1);
	}
	close(i);
	if(!map->east_texture || (i = open(map->east_texture,O_RDONLY)) < 0)
	{
		write(1, "east texture wasnt loaded", 25);
		exit(1);
	}
	close(i);
	if(!map->south_texture || (i = open(map->south_texture,O_RDONLY)) < 0)
	{
		write(1, "south texture wasnt loaded", 26);
		exit(1);
	}
	close(i);
	if(!map->west_texture || (i = open(map->west_texture,O_RDONLY)) < 0)
	{
		write(1, "west texture wasnt loaded", 25);
		exit(1);
	}
	close(i);
}

