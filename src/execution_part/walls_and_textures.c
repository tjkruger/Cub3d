/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_and_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awolschi <awolschi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 20:25:45 by awolschi          #+#    #+#             */
/*   Updated: 2026/06/23 18:49:31 by awolschi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/// @brief 
/// @param ray 
/// @brief Calculates the perpendicular distance from the ray to the wall.
/// @param ray Pointer to the ray structure.
static void	calculate_perp_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
	if (ray->perp_wall_dist <= 0.00001)
		ray->perp_wall_dist = 0.00001;
}

/// @brief Calculates the wall hit position and the screen slice for the ray.
/// @param main Pointer to the main game structure.
/// @param ray Pointer to the ray structure.
static void	calculate_wall_hit_and_slice(t_main *main, t_ray *ray)
{
	float	pos_x;
	float	pos_y;

	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->line_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->line_start < 0)
		ray->line_start = 0;
	ray->line_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->line_end >= HEIGHT)
		ray->line_end = HEIGHT - 1;
	if (ray->side == 0)
	{
		pos_y = main->player->pos.y;
		ray->wall_hit_x = pos_y + ray->perp_wall_dist * ray->dir.y;
	}
	else
	{
		pos_x = main->player->pos.x;
		ray->wall_hit_x = pos_x + ray->perp_wall_dist * ray->dir.x;
	}
	ray->wall_hit_x -= floorf(ray->wall_hit_x);
}

/// @brief Selects the texture index based on the wall side and ray direction.
/// @param ray Pointer to the ray structure.
static int	select_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (2);
		return (3);
	}
	if (ray->dir.y > 0)
		return (1);
	return (0);
}

/// @brief Converts the wall hit position into a valid texture x coordinate.
/// @param main Pointer to the main game structure.
/// @param ray Pointer to the ray structure.
/// @param tex_index Index of the texture to sample.
static void	calculate_texture_x(t_main *main, t_ray *ray, int tex_index)
{
	int	tex_w;

	if (main->textures[tex_index] && main->textures[tex_index]->width > 0)
	{
		tex_w = main->textures[tex_index]->width;
		ray->texture_x = (int)(ray->wall_hit_x * (float)tex_w);
		if ((ray->side == 0 && ray->dir.x > 0) || (ray->side == 1
				&& ray->dir.y < 0))
			ray->texture_x = tex_w - ray->texture_x - 1;
		if (ray->texture_x < 0)
			ray->texture_x = 0;
		if (ray->texture_x >= tex_w)
			ray->texture_x = tex_w - 1;
	}
	else
		ray->texture_x = 0;
}

/// @brief Main function for calculating walls and textures.
/// @param main  Pointer to the main game structure.
/// @param ray Pointer to the ray structure.
/// @param column Index of the current column.
void	calculate_wall_distance(t_main *main, t_ray *ray, int column)
{
	int	tex_index;

	if (!main || !ray || !main->player)
		return ;
	calculate_perp_wall_dist(ray);
	calculate_wall_hit_and_slice(main, ray);
	tex_index = select_texture_index(ray);
	calculate_texture_x(main, ray, tex_index);
	(void)column;
}
