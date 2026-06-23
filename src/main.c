/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 20:10:00 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/23 22:21:38 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

static void	set_project_root(char *exec_path)
{
	char	*resolved;
	char	*slash;

	if (!exec_path)
		return ;
	resolved = realpath(exec_path, NULL);
	if (!resolved)
		return ;
	slash = ft_strrchr(resolved, '/');
	if (slash)
	{
		*slash = '\0';
		chdir(resolved);
	}
	free(resolved);
}

void	exit_error(char *msg, t_main *main)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	(void)main;
	exit(1);
}

int	main(int ac, char **av)
{
	t_main	*main;

	set_project_root(av[0]);
	main = initialise();
	parse(ac, av, main);
	init_player(main);
	load_textures(main);
	run_game(main);
	end_game(main);
	return (EXIT_SUCCESS);
}
