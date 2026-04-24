#include "../include/cub3d.h"

void free_all(t_main *main)
{
    if (!main)
        return;
    free_parser(main->parser);
    free_map_data(main->map_data);
    free(main);
}

void free_parser(t_parser *parser)
{
    if (!parser)
        return;
    free(parser->map_path);
    free_str_array(parser->map_copy);
    free(parser->floor_color);
    free(parser->ceiling_color);
    free(parser);
}

void free_map_data(t_map_data *map_data)
{
    if (!map_data)
        return;
    free(map_data->north_texture);
    free(map_data->south_texture);
    free(map_data->east_texture);
    free(map_data->west_texture);
    free_str_array(map_data->map);
    free(map_data);
}

void free_str_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
