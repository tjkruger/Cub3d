#include "../include/cub3d.h"

uint32_t rgb_to_rgba(int rgb)
{
    uint32_t r;
    uint32_t g;
    uint32_t b;

    r = (uint32_t)((rgb >> 16) & 0xFF);
    g = (uint32_t)((rgb >> 8) & 0xFF);
    b = (uint32_t)(rgb & 0xFF);
    return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

void put_pixel_rgba(mlx_image_t *img, int x, int y, uint32_t color)
{
    uint32_t idx;

    idx = ((uint32_t)y * img->width + (uint32_t)x) * 4;
    img->pixels[idx + 0] = (uint8_t)((color >> 24) & 0xFF);
    img->pixels[idx + 1] = (uint8_t)((color >> 16) & 0xFF);
    img->pixels[idx + 2] = (uint8_t)((color >> 8) & 0xFF);
    img->pixels[idx + 3] = (uint8_t)(color & 0xFF);
}

