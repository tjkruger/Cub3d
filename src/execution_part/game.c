#include "../include/cub3d.h"

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

bool init_game(t_main *main)
{
    main->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
}

static void key_hook(mlx_key_data_t keydata, void *param)
{

}

static void frame_hook(void *param)
{
    t_main *main;
    uint32_t ceiling;
    uint32_t floor;
    int x;
    int y;

    main = (t_main *)param;
    ceiling = rgb_to_rgba(main->map_data->ceiling_color);
    floor = rgb_to_rgba(main->map_data->floor_color);
    y = 0;
    while (y < main->mlx->height)
    {
        x = 0;
        while (x < main->mlx->width)
        {
            if (y < main->mlx->height / 2) 
                main->image->pixels[y * main->mlx->width + x] = ceiling;
            else
                main->image->pixels[y * main->mlx->width + x] = floor;
            x++;
        }
        y++;
    }
}
