#include "../include/cub3d.h"

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
