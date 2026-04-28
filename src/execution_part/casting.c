#include "../include/cub3d.h"

void cast_single_ray(t_main *main, t_ray *ray, int x)
{
    t_point player_pos;

    if (!main || !ray || !main->player)
        return;
    ray->cam_x = 2 * x / WIDTH - 1;
    ray->dir.x = main->player->dir.x + main->player->plane.x * ray->cam_x;
    ray->dir.y = main->player->dir.y + main->player->plane.y * ray->cam_x;
    player_pos.x = (int)main->player->pos.x;
    player_pos.y = (int)main->player->pos.y;
    ray->map_tile = player_pos;
    ray->delta_dist.x = fabsf(1 / ray->dir.x);
    ray->delta_dist.y = fabsf(1 / ray->dir.y);
    init_step_and_side_dist(main, ray);
    perform_dda(main, ray);
    calculate_wall_distance(main, ray, x);
}

void casting_loop(t_main *main)
{
    t_ray ray;
    int x;

    if (!main || !main->player || !main->map_data)
        return;
    x = 0;
    while (x < WIDTH)
    {
        cast_single_ray(main, &ray, x);
        x++;
    }
}

void init_step_and_side_dist(t_main *main, t_ray *ray)
{

}

void perform_dda(t_main *main, t_ray *ray)
{

}

void calculate_wall_distance(t_main *main, t_ray *ray, int column)
{

}

