#include "cub3d.h"

#include "../include/cub3d.h"

static void move_forward_back(t_main *main, float dir)
{
    float new_x = main->player->pos.x + main->player->dir.x * main->player->speed * dir;
    float new_y = main->player->pos.y + main->player->dir.y * main->player->speed * dir;

    // check wall collision before moving
    if (main->map_data->map[(int)main->player->pos.y][(int)new_x] != '1')
        main->player->pos.x = new_x;
    if (main->map_data->map[(int)new_y][(int)main->player->pos.x] != '1')
        main->player->pos.y = new_y;
}

static void strafe(t_main *main, float dir)
{
    float new_x = main->player->pos.x + main->player->plane.x * main->player->speed * dir;
    float new_y = main->player->pos.y + main->player->plane.y * main->player->speed * dir;

    if (main->map_data->map[(int)main->player->pos.y][(int)new_x] != '1')
        main->player->pos.x = new_x;
    if (main->map_data->map[(int)new_y][(int)main->player->pos.x] != '1')
        main->player->pos.y = new_y;
}

static void rotate(t_main *main, float angle)
{
    float old_dir_x = main->player->dir.x;
    float old_plane_x = main->player->plane.x;

    // rotate direction vector
    main->player->dir.x = main->player->dir.x * cos(angle) - main->player->dir.y * sin(angle);
    main->player->dir.y = old_dir_x             * sin(angle) + main->player->dir.y * cos(angle);

    // rotate camera plane by same angle (keeps FOV correct)
    main->player->plane.x = main->player->plane.x * cos(angle) - main->player->plane.y * sin(angle);
    main->player->plane.y = old_plane_x             * sin(angle) + main->player->plane.y * cos(angle);
}

void handle_movement(t_main *main)
{
    if (mlx_is_key_down(main->mlx, MLX_KEY_W))
        move_forward_back(main, 1.0f);
    if (mlx_is_key_down(main->mlx, MLX_KEY_S))
        move_forward_back(main, -1.0f);
    if (mlx_is_key_down(main->mlx, MLX_KEY_A))
        strafe(main, -1.0f);
    if (mlx_is_key_down(main->mlx, MLX_KEY_D))
        strafe(main, 1.0f);
    if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT))
        rotate(main, -ROTATION_SPEED);
    if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
        rotate(main, ROTATION_SPEED);
}