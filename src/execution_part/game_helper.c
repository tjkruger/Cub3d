#include "../include/cub3d.h"

/// @brief Converts RGB color to RGBA format with full alpha opacity
/// @param rgb RGB color value (24-bit: 0xRRGGBB)
/// @return RGBA color value with alpha set to 0xFF
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

/// @brief Puts a pixel with RGBA color at specified coordinates in the image
/// @param img Pointer to the image to draw on
/// @param x X coordinate of the pixel
/// @param y Y coordinate of the pixel
/// @param color RGBA color value
void put_pixel_rgba(mlx_image_t *img, int x, int y, uint32_t color)
{
    if (!img || x < 0 || y < 0 || x >= (int)img->width || y >= (int)img->height)
        return;
    mlx_put_pixel(img, (uint32_t)x, (uint32_t)y, color);
}

