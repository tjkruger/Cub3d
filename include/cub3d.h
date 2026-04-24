

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
//# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080
# define PLAYER_SPEED 0.1
# define ROTATION_SPEED 0.05
# define FOV 0.9

/* ************************************************************************** */
/*   Basic types                                                              */
/* ************************************************************************** */

typedef struct s_vec
{
	float			x;
	float			y;
}					t_vec;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

/* ************************************************************************** */
/*   Parser staging area - raw data from .cub file before validation          */
/* ************************************************************************** */

typedef struct s_parser
{
	char			*map_path;
	char			**map_copy;
	int				map_fd;
	int				last_type_index;
	char			*floor_color;
	char			*ceiling_color;
}					t_parser;

/* ************************************************************************** */
/*   Map data - clean validated data extracted from the .cub file             */
/* ************************************************************************** */

typedef struct s_map_data
{
	char			*north_texture;
	char			*east_texture;
	char			*south_texture;
	char			*west_texture;
	int				floor_color;
	int				ceiling_color;
	char			**map;
	int				map_width;
	int				map_height;
	char			player_orientation;
	t_point			player_pos;
}					t_map_data;

/* ************************************************************************** */
/*   Player - position, direction and camera plane for DDA raycasting         */
/* ************************************************************************** */

typedef struct s_player
{
	t_vec			pos;
	t_vec			dir;
	t_vec			plane;
	float			speed;
}					t_player;

/* ************************************************************************** */
/*   Ray - state for one column of the screen during DDA                      */
/* ************************************************************************** */

typedef struct s_ray
{
	t_vec			dir;
	t_vec			side_dist;
	t_vec			delta_dist;
	float			cam_x;
	float			perp_wall_dist;
	float			wall_hit_x;
	t_point			map_tile;
	t_point			step;
	int				texture_x;
	int				line_height;
	int				line_start;
	int				line_end;
	int				side;
	bool			hit;
}					t_ray;

/* ************************************************************************** */
/*   Main - god struct, one pointer to rule them all                          */
/* ************************************************************************** */

typedef struct s_main
{
	t_parser		*parser;
	t_map_data		*map_data;
	t_player		*player;
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*textures[4];
}					t_main;

/* ************************************************************************** */
/*   Function prototypes - fill these in as you go                            */
/* ************************************************************************** */

// init.c
t_main				*init_structs(void);

// parse.c
void				parse(int ac, char **av, t_main *main);

// game.c
void				run_game(t_main *main);
void				end_game(t_main *main);

// free.c
void				free_all(t_main *main);

// init.c
void				init_player(t_main *main);

// textures.c
void				load_textures(t_main *main);
void				free_textures(t_main *main);

#endif