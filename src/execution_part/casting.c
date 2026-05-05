#include "../include/cub3d.h"

/// @brief Casts a single ray for the given x coordinate
/// @param main Pointer to the main game structure
/// @param ray Pointer to the ray structure
/// @param x X coordinate for which to cast the ray
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

/// @brief Main loop for casting rays and rendering the scene
/// @param main Pointer to the main game structure
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
        int tex_index = 0;
        if (ray.side == 0)
        {
            if (ray.dir.x > 0)
                tex_index = 2;
            else
                tex_index = 3;
        }
        else
        {
            if (ray.dir.y > 0)
                tex_index = 1;
            else
                tex_index = 0;
        }

        mlx_texture_t *tex = NULL;
        if (tex_index >= 0 && tex_index < 4)
            tex = main->textures[tex_index];

        if (tex && tex->width > 0 && tex->height > 0)
        {
            int tex_w = (int)tex->width;
            int tex_h = (int)tex->height;
            int y;
            for (y = ray.line_start; y <= ray.line_end; y++)
            {
                int d = y * 256 - HEIGHT * 128 + ray.line_height * 128;
                int tex_y = ((d * tex_h) / ray.line_height) / 256;
                if (tex_y < 0) tex_y = 0;
                if (tex_y >= tex_h) tex_y = tex_h - 1;
                int tex_x = ray.texture_x;
                if (tex_x < 0) tex_x = 0;
                if (tex_x >= tex_w) tex_x = tex_w - 1;
                uint8_t *p = &tex->pixels[(tex_y * tex_w + tex_x) * tex->bytes_per_pixel];
                uint8_t r = p[0];
                uint8_t g = p[1];
                uint8_t b = p[2];
                uint8_t a = (tex->bytes_per_pixel > 3) ? p[3] : 0xFF;
                uint32_t color = ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a;
                put_pixel_rgba(main->image, x, y, color);
            }
        }
        else
        {
            int y;
            uint32_t mag = (255u << 24) | (0u << 16) | (255u << 8) | 255u;
            for (y = ray.line_start; y <= ray.line_end; y++)
                put_pixel_rgba(main->image, x, y, mag);
        }

        x++;
    }
}

/// @brief Initializes the step and side distance for DDA algorithm
/// @param main Pointer to the main game structure
/// @param ray Pointer to the ray structure
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

/// @brief Performs the DDA (Digital Differential Analysis) algorithm
/// @param main Pointer to the main game structure
/// @param ray Pointer to the ray structure
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

/// @brief Calculates the distance to the wall hit by the ray and determines texture coordinates
/// @param main Pointer to the main game structure
/// @param ray Pointer to the ray structure
/// @param column X coordinate for which to calculate wall distance
void calculate_wall_distance(t_main *main, t_ray *ray, int column)
{
    if (!main || !ray || !main->player)
        return;
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
    else
        ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
    if (ray->perp_wall_dist <= 0.00001)
        ray->perp_wall_dist = 0.00001;
    ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
    ray->line_start = -ray->line_height / 2 + HEIGHT / 2;
    if (ray->line_start < 0)
        ray->line_start = 0;
    ray->line_end = ray->line_height / 2 + HEIGHT / 2;
    if (ray->line_end >= HEIGHT)
        ray->line_end = HEIGHT - 1;
    {
        float pos_x = main->player->pos.x;
        float pos_y = main->player->pos.y;
        if (ray->side == 0)
            ray->wall_hit_x = pos_y + ray->perp_wall_dist * ray->dir.y;
        else
            ray->wall_hit_x = pos_x + ray->perp_wall_dist * ray->dir.x;
        ray->wall_hit_x -= floorf(ray->wall_hit_x);
    }
    int tex_index = 0;
    if (ray->side == 0)
    {
        if (ray->dir.x > 0)
            tex_index = 2;
        else
            tex_index = 3;
    }
    else
    {
        if (ray->dir.y > 0)
            tex_index = 1;
        else
            tex_index = 0;
    }

    if (main->textures[tex_index] && main->textures[tex_index]->width > 0)
    {
        int tex_w = main->textures[tex_index]->width;
        ray->texture_x = (int)(ray->wall_hit_x * (float)tex_w);
        if ((ray->side == 0 && ray->dir.x > 0) || (ray->side == 1 && ray->dir.y < 0))
            ray->texture_x = tex_w - ray->texture_x - 1;
        if (ray->texture_x < 0) ray->texture_x = 0;
        if (ray->texture_x >= tex_w) ray->texture_x = tex_w - 1;
    }
    else
    {
        ray->texture_x = 0;
    }

    (void)column;
}
