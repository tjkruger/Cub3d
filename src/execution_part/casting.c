#include "../include/cub3d.h"

void cast_single_ray(t_main *main, t_ray *ray, int x)
{
    t_point	player_pos;

    if (!main || !ray || !main->player)
        return ;
    ray->cam_x = (2.0f * (float)x / (float)WIDTH) - 1.0f;
    ray->dir.x = main->player->dir.x + main->player->plane.x * ray->cam_x;
    ray->dir.y = main->player->dir.y + main->player->plane.y * ray->cam_x;
    player_pos.x = (int)main->player->pos.x;
    player_pos.y = (int)main->player->pos.y;
    ray->map_tile = player_pos;
    if (ray->dir.x == 0.0f)
        ray->delta_dist.x = 1e30f;
    else
        ray->delta_dist.x = fabsf(1.0f / ray->dir.x);
    if (ray->dir.y == 0.0f)
        ray->delta_dist.y = 1e30f;
    else
        ray->delta_dist.y = fabsf(1.0f / ray->dir.y);
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
    float pos_x;
    float pos_y;
    int map_x;
    int map_y;
    if (!main || !ray || !main->player)
        return;
    pos_x = main->player->pos.x;
    pos_y = main->player->pos.y;
    map_x = ray->map_tile.x;
    map_y = ray->map_tile.y;
    if (ray->dir.x < 0)
    {
        ray->step.x = -1;
        ray->side_dist.x = (pos_x - map_x) * ray->delta_dist.x;
    }
    else
    {
        ray->step.x = 1;
        ray->side_dist.x = (map_x + 1.0 - pos_x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step.y = -1;
        ray->side_dist.y = (pos_y - map_y) * ray->delta_dist.y;
    }
    else
    {
        ray->step.y = 1;
        ray->side_dist.y = (map_y + 1.0 - pos_y) * ray->delta_dist.y;
    }
}

void perform_dda(t_main *main, t_ray *ray)
{
    if(!main || !ray || !main->map_data || !main->map_data->map)
        return;
    ray->hit = false;
    while(!ray->hit)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map_tile.x += ray->step.x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            ray->map_tile.y += ray->step.y;
            ray->side = 1;
        }
        if (ray->map_tile.x < 0 || ray->map_tile.y < 0
            || ray->map_tile.x >= main->map_data->map_width
            || ray->map_tile.y >= main->map_data->map_height)
            ray->hit = true;
        else if (main->map_data->map[ray->map_tile.y][ray->map_tile.x] == '1'
            || main->map_data->map[ray->map_tile.y][ray->map_tile.x] == ' ')
            ray->hit = true;
    }
}

void calculate_wall_distance(t_main *main, t_ray *ray, int column)
{

}

