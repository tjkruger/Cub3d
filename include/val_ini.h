#ifndef VAL_INI.H
# define VAL_INI.H

#include "cub3d.h"


//file validation
void	check_extension(char *path);
void	check_args(int ac, char **av, t_parser *parser);
int     is_identifier(char *line, char *id);
char	*extract_value(char *line);
void	validate_textures(t_map_data *map);


//file parsing
void	copy_file_blindly(t_main *main);
void	parse_colours(t_map_data *map, t_parser *parser);
void	parse(int ac, char **av, t_main *main);

//initialisation
t_main *initialise();
int	    store_identifier(char *line, t_map_data *map_data, t_parser *parser);
void	get_height_and_length(t_map_data *map);


//check map
void    validate_map(t_map_data *map_data);
int	    is_map_line(char *line);
int 	make_map(char *line, t_map_data *map);
char    **make_map_copy(char **map, int height);
void    floodfill(char **map, int x, int y, int width, int height);


#endif