#include "../include/cub3d.h"

void init_player(t_main *main)
{
    if (!main || !main->map_data)
        error_exit("Invalid main struct or map data");
    main->player = malloc(sizeof(t_player));
    if (!main->player)
        error_exit("Failed to allocate memory for player");
    set_player_position(main);
    set_player_orientation(main);
    set_player_speed(main);
}

static void set_player_position(t_main *main)
{
    main->player->pos.x = (float)main->map_data->player_pos.x + 0.5f;
    main->player->pos.y = (float)main->map_data->player_pos.y + 0.5f;
}

static void set_player_orientation(t_main *main)
{
    if (main->map_data->player_orientation == 'N')
    {
        main->player->dir = (t_vec){0.0f, -1.0f};
        main->player->plane = (t_vec){0.66f, 0.0f};
    }
    else if (main->map_data->player_orientation == 'S')
    {
        main->player->dir = (t_vec){0.0f, 1.0f};
        main->player->plane = (t_vec){-0.66f, 0.0f};
    }
    else if (main->map_data->player_orientation == 'E')
    {
        main->player->dir = (t_vec){1.0f, 0.0f};
        main->player->plane = (t_vec){0.0f, 0.66f};
    }
    else if (main->map_data->player_orientation == 'W')
    {
        main->player->dir = (t_vec){-1.0f, 0.0f};
        main->player->plane = (t_vec){0.0f, -0.66f};
    }
}

static void set_player_speed(t_main *main)
{
    main->player->speed = 0.05f; // placeholder
}
