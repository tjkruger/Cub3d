#include "../include/cub3d.h"

static void set_player_position(t_main *main);
static void set_player_orientation(t_main *main);
static void set_player_speed(t_main *main);

/// @brief Allocates and initializes all main game structures
/// @return Pointer to the newly allocated main structure, or NULL on failure
t_main	*init_structs(void)
{
    t_main	*main;

    main = calloc(1, sizeof(t_main));
    if (!main)
        return (NULL);
    main->parser = calloc(1, sizeof(t_parser));
    main->map_data = calloc(1, sizeof(t_map_data));
    main->player = calloc(1, sizeof(t_player));
    if (!main->parser || !main->map_data || !main->player)
    {
        free(main->player);
        free(main->map_data);
        free(main->parser);
        free(main);
        error_exit("Failed to allocate memory for main structs");
    }
    return (main);
}

/// @brief Initializes the player with position, orientation, and speed
/// @param main Pointer to the main game structure
void init_player(t_main *main)
{
    if (!main || !main->map_data || !main->player)
        error_exit("Invalid main struct or map data");
    set_player_position(main);
    set_player_orientation(main);
    set_player_speed(main);
}

/// @brief Sets the player's position based on map data
/// @param main Pointer to the main game structure
static void set_player_position(t_main *main)
{
    main->player->pos.x = (float)main->map_data->player_pos.x + 0.5f;
    main->player->pos.y = (float)main->map_data->player_pos.y + 0.5f;
}

/// @brief Sets the player's direction and camera plane based on orientation
/// @param main Pointer to the main game structure
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
    else
        error_exit("Invalid player orientation in map data");
}

/// @brief Sets the player's movement speed
/// @param main Pointer to the main game structure
static void set_player_speed(t_main *main)
{
    main->player->speed = 0.05f; // placeholder
}
