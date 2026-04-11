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
		parser->floor_color = extract_value(line);
	else if (is_identifier(line, "C"))
		parser->ceiling_color = extract_value(line);
	else
		return (0);
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '1' || line[i] == '0');
}

void	read_file(t_main *main)
{
	char	*line;
	int		headers_found;

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
	// line currently holds the first map line — handle map reading next task
	free(line);
}

void	parse(int ac, char **av, t_main *main)
{
	check_args(ac, av, main->parser);
	read_file(main);
}