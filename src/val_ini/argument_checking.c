/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_checking.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 22:09:09 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 22:22:22 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension(char *path)
{
	int	len;

	len = 0;
	while (path[len])
		len++;
	if (len < 5 || path[len - 4] != '.' || path[len - 3] != 'c'
		|| path[len - 2] != 'u' || path[len - 1] != 'b')
	{
		write(2, "Error\nInvalid file extension, expected .cub\n", 44);
		exit(1);
	}
}

// check the input for mistakes
void	check_args(int ac, char **av, t_parser *parser)
{
	if (ac != 2)
	{
		write(2, "Error\nUsage: ./cub3d <map.cub>\n", 31);
		exit(1);
	}
	check_extension(av[1]);
	parser->map_fd = open(av[1], O_RDONLY);
	if (parser->map_fd < 0)
	{
		write(2, "Error\nCould not open map file\n", 30);
		exit(1);
	}
	parser->map_path = av[1];
}
