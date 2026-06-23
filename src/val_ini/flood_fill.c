/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 21:59:19 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 21:59:40 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_error(void)
{
	write(2, "Error\nMap is not enclosed\n", 25);
	exit(1);
}

static int	is_out_of_bounds(t_flood *f, int x, int y)
{
	return (y < 0 || y >= f->height || x < 0 || x >= f->width
		|| x >= (int)ft_strlen(f->map[y]));
}

void	floodfill(t_flood *f, int x, int y)
{
	if (is_out_of_bounds(f, x, y))
		flood_error();
	if (f->map[y][x] == '1' || f->map[y][x] == 'V')
		return ;
	if (f->map[y][x] == ' ')
		flood_error();
	f->map[y][x] = 'V';
	floodfill(f, x + 1, y);
	floodfill(f, x - 1, y);
	floodfill(f, x, y + 1);
	floodfill(f, x, y - 1);
}
