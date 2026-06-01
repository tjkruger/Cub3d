#include "../include/cub3d.h"

static void key_hook(mlx_key_data_t keydata, void *param);
static void frame_hook(void *param);

/// @brief Initializes the game and starts the main loop
/// @param main Pointer to the main game structure
void				run_game(t_main *main)
{
    if (!main)
        error_exit("Invalid main struct");
    if (!init_game(main))
    {
        end_game(main);
        error_exit("Failed to initialize game");
    }
    mlx_loop_hook(main->mlx, frame_hook, main);
    mlx_key_hook(main->mlx, key_hook, main);
    mlx_loop(main->mlx);
}

/// @brief Cleans up and terminates the game
/// @param main Pointer to the main game structure
void				end_game(t_main *main)
{
    if(!main)
        return;
    free_textures(main);
    if (main->mlx && main->image)
        mlx_delete_image(main->mlx, main->image);
    if (main->mlx)
        mlx_terminate(main->mlx);
    free_all(main);
}

/// @brief Initializes the MLX window and framebuffer image
/// @param main Pointer to the main game structure
/// @return true on success, false on failure
bool init_game(t_main *main)
{
    if (!main)
        return false;
    main->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
    if (!main->mlx)
        return false;
    main->image = mlx_new_image(main->mlx, WIDTH, HEIGHT);
    if (!main->image)    
    {
        mlx_terminate(main->mlx);
        main->mlx = NULL;
        return false;
    }
    if (mlx_image_to_window(main->mlx, main->image, 0, 0) < 0)
    {
        mlx_delete_image(main->mlx, main->image);
        main->image = NULL;
        mlx_terminate(main->mlx);
        main->mlx = NULL;
        return false;
    }
    return true;
}

/// @brief Handles keyboard input events
/// @param keydata Keyboard event data
/// @param param User parameter (pointer to t_main)
static void key_hook(mlx_key_data_t keydata, void *param)
{
	t_main *main = (t_main *)param;
    
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(main->mlx);
}

/// @brief Called every frame to render the game
/// @param param User parameter (pointer to t_main)
static void frame_hook(void *param)
{
    t_main *main;
    uint32_t ceiling;
    uint32_t floor;
    int x;
    int y;

    main = (t_main *)param;
    handle_movement(main);
    ceiling = rgb_to_rgba(main->map_data->ceiling_color);
    floor = rgb_to_rgba(main->map_data->floor_color);
    y = 0;
    while (y < main->mlx->height)
    {
        x = 0;
        while (x < main->mlx->width)
        {
            if (y < main->mlx->height / 2)
                put_pixel_rgba(main->image, x, y, ceiling);
            else
                put_pixel_rgba(main->image, x, y, floor);
            x++;
        }
        y++;
    }
    casting_loop(main);
}
