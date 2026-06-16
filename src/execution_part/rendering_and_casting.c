/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_and_casting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awolschi <awolschi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 20:25:39 by awolschi          #+#    #+#             */
/*   Updated: 2026/06/16 20:25:41 by awolschi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static mlx_texture_t	*get_texture(t_main *main, int tex_index)
{
	if (tex_index < 0 || tex_index >= 4)
		return (NULL);
	return (main->textures[tex_index]);
}

static void	put_textured_pixel(t_main *main, t_ray ray, int x, int y,
	mlx_texture_t *tex)
{
	int		tex_w;
	int		tex_h;
	int		tex_x;
	int		tex_y;
	int		d;
	uint8_t		*p;
	uint32_t	color;

	tex_w = (int)tex->width;
	tex_h = (int)tex->height;
	d = y * 256 - HEIGHT * 128 + ray.line_height * 128;
	tex_y = ((d * tex_h) / ray.line_height) / 256;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_h)
		tex_y = tex_h - 1;
	tex_x = ray.texture_x;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_w)
		tex_x = tex_w - 1;
	p = &tex->pixels[(tex_y * tex_w + tex_x) * tex->bytes_per_pixel];
	color = ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16);
	color |= ((uint32_t)p[2] << 8);
	if (tex->bytes_per_pixel > 3)
		color |= (uint32_t)p[3];
	else
		color |= (uint32_t)0xFF;
	put_pixel_rgba(main->image, x, y, color);
}

static void	draw_textured_column(t_main *main, t_ray ray, int x,
	mlx_texture_t *tex)
{
	int	y;

	y = ray.line_start;
	while (y <= ray.line_end)
	{
		put_textured_pixel(main, ray, x, y, tex);
		y++;
	}
}

/// @brief Main loop for casting rays and rendering the scene
/// @param main Pointer to the main game structure
void casting_loop(t_main *main)
{
	t_ray			 ray;
	int			 x;
	int			 tex_index;
	mlx_texture_t	*tex;

	if (!main || !main->player || !main->map_data)
		return;
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
