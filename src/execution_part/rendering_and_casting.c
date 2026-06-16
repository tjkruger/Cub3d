/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_and_casting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awolschi <awolschi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 20:25:39 by awolschi          #+#    #+#             */
/*   Updated: 2026/06/16 22:40:30 by awolschi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/// @brief Selects the texture index based on the ray direction and side hit
/// @param ray Ray data used to determine which wall texture to draw
static int	get_texture_index(t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.dir.x > 0)
			return (2);
		return (3);
	}
	if (ray.dir.y > 0)
		return (1);
	return (0);
}

/// @brief Returns the texture at the given index if it is valid
/// @param main Pointer to the main game structure
/// @param tex_index Index of the texture to fetch
static mlx_texture_t	*get_texture(t_main *main, int tex_index)
{
	if (tex_index < 0 || tex_index >= 4)
		return (NULL);
	return (main->textures[tex_index]);
}

/// @brief Reads the color of a single texel for the current ray position
/// @param tex Pointer to the texture being sampled
/// @param ray Ray data used to calculate the texture coordinates
/// @param y Screen y coordinate for the current pixel
static uint32_t	get_texel_color(mlx_texture_t *tex, t_ray ray, int y)
{
	uint8_t		*p;
	int			tex_y;
	int			tex_x;
	int			d;
	uint32_t	color;

	d = y * 256 - HEIGHT * 128 + ray.line_height * 128;
	tex_y = ((d * (int)tex->height) / ray.line_height) / 256;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)tex->height)
		tex_y = (int)tex->height - 1;
	tex_x = ray.texture_x;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)tex->width)
		tex_x = (int)tex->width - 1;
	p = &tex->pixels[(tex_y * (int)tex->width + tex_x) * tex->bytes_per_pixel];
	color = ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16);
	color |= ((uint32_t)p[2] << 8);
	if (tex->bytes_per_pixel > 3)
		color |= (uint32_t)p[3];
	else
		color |= (uint32_t)0xFF;
	return (color);
}

/// @brief Draws one vertical textured column on the screen
/// @param main Pointer to the main game structure
/// @param ray Ray data for the current column
/// @param x Screen x coordinate for the column
/// @param tex Texture used for rendering the wall column
static void	draw_textured_column(t_main *main, t_ray ray, int x,
		mlx_texture_t *tex)
{
	int	y;

	y = ray.line_start;
	while (y <= ray.line_end)
	{
		put_pixel_rgba(main->image, x, y, get_texel_color(tex, ray, y));
		y++;
	}
}

/// @brief Main loop for casting rays and rendering the scene
/// @param main Pointer to the main game structure
void	casting_loop(t_main *main)
{
	t_ray			ray;
	int				x;
	int				tex_index;
	mlx_texture_t	*tex;

	if (!main || !main->player || !main->map_data)
		return ;
	x = 0;
	while (x < WIDTH)
	{
		cast_single_ray(main, &ray, x);
		tex_index = get_texture_index(ray);
		tex = get_texture(main, tex_index);
		if (tex && tex->width > 0 && tex->height > 0)
			draw_textured_column(main, ray, x, tex);
		x++;
	}
}
