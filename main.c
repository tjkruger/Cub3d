#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

int	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(1920, 1080, "cub3d", true);
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}