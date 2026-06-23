/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_and_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awolschi <awolschi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 20:25:45 by awolschi          #+#    #+#             */
/*   Updated: 2026/06/23 18:18:15 by awolschi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/// @brief Calculates the distance to the wall hit by the ray and determines texture coordinates
/// @param main Pointer to the main game structure
/// @param ray Pointer to the ray structure
/// @param column X coordinate for which to calculate wall distance
void	calculate_wall_distance(t_main *main, t_ray *ray, int column)
{
	float	pos_x;
	float	pos_y;
	int		tex_index;
	int		tex_w;

	if (!main || !ray || !main->player)
		return ;
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
		pos_x = main->player->pos.x;
		pos_y = main->player->pos.y;
		if (ray->side == 0)
			ray->wall_hit_x = pos_y + ray->perp_wall_dist * ray->dir.y;
		else
			ray->wall_hit_x = pos_x + ray->perp_wall_dist * ray->dir.x;
		ray->wall_hit_x -= floorf(ray->wall_hit_x);
	}
	tex_index = 0;
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
	{
		ray->texture_x = 0;
	}
	(void)column;
}

void	calculate_wall_distance(t_main *main, t_ray *ray, int column)
{
	int tex_index;
	if (!main || !ray || !main->player)
		return;
    calculate_perp_wall_dist(ray);
    calculate_wall_hit(main, ray);
    tex_index = select_texture(ray);
    calculate_texture(main, ray, tex_index);
    (void)column;
}

static void	calculate_perp_wall_dist()
{
	
}

static void	calculate_wall_hit()
{

}

static int	select_texture()
{

}

static void	calculate_texture()
{

}
