#include "../include/cub3d.h"

static void clear_loaded_textures(t_main *main, int last_index)
{
    while (last_index >= 0)
    {
        if (main->textures[last_index])
        {
            mlx_delete_texture(main->textures[last_index]);
            main->textures[last_index] = NULL;
        }
        last_index--;
    }
}

void load_textures(t_main *main)
{
    int i;

    if (!main || !main->map_data)
        error_exit("Invalid main struct or map data");
    main->textures[0] = mlx_load_png(main->map_data->north_texture);
    main->textures[1] = mlx_load_png(main->map_data->south_texture);
    main->textures[2] = mlx_load_png(main->map_data->east_texture);
    main->textures[3] = mlx_load_png(main->map_data->west_texture);
    i = 0;
    while (i < 4)
    {
        if (!main->textures[i])
        {
            clear_loaded_textures(main, i - 1);
            error_exit("Failed to load texture");
        }
        i++;
    }
}

void free_textures(t_main *main)
{
    int i;

    if (!main)
        return;
    i = 0;
    while (i < 4)
    {
        if (main->textures[i])
        {
            mlx_delete_texture(main->textures[i]);
            main->textures[i] = NULL;
        }
        i++;
    }
}
