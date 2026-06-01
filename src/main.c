#include <stdlib.h>
#include "../include/cub3d.h"

static void	set_project_root(char *exec_path)
{
	char	*resolved;
	char	*slash;

	if (!exec_path)
		return;
	resolved = realpath(exec_path, NULL);
	if (!resolved)
		return;
	slash = ft_strrchr(resolved, '/');
	if (slash)
	{
		*slash = '\0';
		chdir(resolved);
	}
	free(resolved);
}

void exit_error(char *msg, t_main *main)
{
    write(2, "Error\n", 6);
    write(2, msg, ft_strlen(msg));
	(void) main;
//    if (main)
//        free_all(main);
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
