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

int	make_map(char *line, t_map_data *map)
{
	static char *all = NULL;
	int i = 0;
	if(!line)
	{
		map->map = ft_split(all, '\n');
		free(all);
		return(0);
	}
	while(line[i] != '\0')
	{
		if(!(line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'E' || line[i] == 'S' || line[i] == 'W' || line[i] == ' ' || line[i] == '\n'))
			break;
		i++;
	}	
	if(line[i] == '\0')
		all = ft_strjoin(all, line);
	else
	{
		map->map = ft_split(all, '\n');
		free(all);
		return(0);
	}
	return(1);
}

void	get_height_and_length(t_map_data *map)
{
	int i = 0;
	int j = 0;
	int len = 0;
	int p_counter = 0;
	while(map->map[i] != NULL)
	{
		while(map->map[i][j] != '\0')
		{
			if(map->map[i][j] == 'N' || map->map[i][j] == 'E' || map->map[i][j] == 'S' || map->map[i][j] == 'W')
			{
				if(p_counter > 1)
				{
					write(1, "multiple player pos", 19);
					exit(1);
				}
				map->player_orientation = map->map[i][j];
				map->player_pos.x = j;
				map->player_pos.y = i;
				p_counter++;
			}
			j++;
		}
		if(j > len)
			len = j;
		j = 0;
		i++;
	}
	map->map_height = i;
	map->map_width = len;
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


void	validate_textures(t_map_data *map)
{
	int i = 0;
	if(map->north_texture || (i = open(map->north_texture,O_RDONLY)) < 0)
	{
		write(1, "north texture wasnt loaded", 26);
		exit(1);
	}
	close(i);
	if(map->east_texture || (i = open(map->east_texture,O_RDONLY)) < 0)
	{
		write(1, "east texture wasnt loaded", 25);
		exit(1);
	}
	close(i);
	if(map->south_texture || (i = open(map->south_texture,O_RDONLY)) < 0)
	{
		write(1, "south texture wasnt loaded", 26);
		exit(1);
	}
	close(i);
	if(map->west_texture || (i = open(map->west_texture,O_RDONLY)) < 0)
	{
		write(1, "west texture wasnt loaded", 25);
		exit(1);
	}
	close(i);
}

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

char **make_map_copy(char **map, int height)
{
    char **copy;
    int i = 0;
    int j = 0;

    copy = malloc(sizeof(char *) * (height + 1));
    while(height > i)
    {
        j = 0;
        copy[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
        while(map[i][j] != '\0')
        {
            copy[i][j] = map[i][j];
            j++;
        }
        copy[i][j] = '\0';
        i++;
    }
    copy[i] = NULL;
    return(copy);
}

void floodfill(char **map, int x, int y, int width, int height)
{
    if (y < 0 || y >= height || x < 0 || x >= width)
    {
        write(2, "Error\nMap is not enclosed\n", 25);
        exit(1);
    }
    if (map[y][x] == '1' || map[y][x] == 'V')
        return;
    if (map[y][x] == ' ')
    {
        write(2, "Error\nMap is not enclosed\n", 25);
        exit(1);
    }
    map[y][x] = 'V';
    floodfill(map, x + 1, y, width, height);
    floodfill(map, x - 1, y, width, height);
    floodfill(map, x, y + 1, width, height);
    floodfill(map, x, y - 1, width, height);
}

void    validate_map(t_map_data *map_data)
{
    char    **copy;
    int     x;
    int     y;

    copy = make_map_copy(map_data->map, map_data->map_height);
    floodfill(copy, map_data->player_pos.x, map_data->player_pos.y,
              map_data->map_width, map_data->map_height);
    y = 0;
    while (copy[y])
    {
        x = 0;
        while (copy[y][x])
        {
            if (copy[y][x] == '0')
            {
                write(2, "Error\nMap has unreachable areas\n", 32);
                exit(1);
            }
            x++;
        }
        y++;
    }
    y = 0;
    while (copy[y])
        free(copy[y++]);
    free(copy);
}

void	parse(int ac, char **av, t_main *main)
{
	check_args(ac, av, main->parser);
	copy_file_blindly(main);
	validate_textures(main->map_data);
	parse_colours(main->map_data, main->parser);
    validate_map(main->map_data);
}