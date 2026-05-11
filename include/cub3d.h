

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

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

# include "get_next_line.h"
# include "val_ini.h"

/* ************************************************************************** */
/*   Function prototypes - fill these in as you go                            */
/* ************************************************************************** */

// game.c
void				run_game(t_main *main);
void				end_game(t_main *main);
bool				init_game(t_main *main);

// game_helper.c
uint32_t			rgb_to_rgba(int rgb);
void				put_pixel_rgba(mlx_image_t *img, int x, int y, uint32_t color);

// free.c
void				free_all(t_main *main);
void				exit_error(char *msg, t_main *main);

// init.c
void				init_player(t_main *main);

// textures.c
void				load_textures(t_main *main);
void				free_textures(t_main *main);

// casting.c
void				casting_loop(t_main *main);
void				cast_single_ray(t_main *main, t_ray *ray, int x);
void				init_step_and_side_dist(t_main *main, t_ray *ray);
void				perform_dda(t_main *main, t_ray *ray);
void				calculate_wall_distance(t_main *main, t_ray *ray, int column);

// error.c
void				error_exit(const char *message);

/* ************************************************************************** */
/*   Libft declarations (minimal subset)                                       */
/* ************************************************************************** */
// int					ft_strlen(const char *s);
// int					ft_atoi(const char *str);
// char				*ft_strdup(const char *s1);
// char				*ft_strtrim(char const *s1, char const *set);
// int					ft_strncmp(const char *s1, const char *s2, size_t n);
// char				**ft_split(char const *s, char c);
// void				ft_free_split(char **split);
// char				*get_next_line(int fd);

#endif