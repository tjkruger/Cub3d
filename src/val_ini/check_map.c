/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:47:01 by tjkruger          #+#    #+#             */
/*   Updated: 2026/04/25 16:48:50 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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