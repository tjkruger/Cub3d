#include "../include/cub3d.h"

/// @brief Frees all strings in an array and the array itself
/// @param array Pointer to the string array to free
static void free_str_array(char **array)
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

/// @brief Frees all memory allocated by the parser structure
/// @param parser Pointer to the parser structure to free
static void free_parser(t_parser *parser)
{
    if (!parser)
        return;
    free(parser->map_path);
    free_str_array(parser->map_copy);
    free(parser->floor_color);
    free(parser->ceiling_color);
    free(parser);
}

/// @brief Frees all memory allocated by the map data structure
/// @param map_data Pointer to the map data structure to free
static void free_map_data(t_map_data *map_data)
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

/// @brief Frees all allocated memory in the main structure
/// @param main Pointer to the main game structure to free
void free_all(t_main *main)
{
    if (!main)
        return;
    free_parser(main->parser);
    free_map_data(main->map_data);
    free(main->player);
    free(main);
}
