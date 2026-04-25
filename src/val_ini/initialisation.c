/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:43:28 by tjkruger          #+#    #+#             */
/*   Updated: 2026/04/25 16:44:12 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_main *initialise()
{
    int i = 0;
    t_main *main = malloc(sizeof(t_main));
    if(!main)
        return(NULL);
    main->parser        = NULL;
    main->image         = NULL;
    main->map_data      = NULL;
    main->mlx           = NULL;
    main->player        = NULL;
    while(i < 4)
    {
        main->textures[i]   = NULL;
        i++;
    }
    return(main);
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
				if(p_counter > 0)
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