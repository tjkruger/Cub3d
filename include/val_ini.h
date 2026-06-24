/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_ini.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 22:26:05 by tjkruger          #+#    #+#             */
/*   Updated: 2026/06/24 08:26:53 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAL_INI_H
# define VAL_INI_H

// file validation
void	check_extension(char *path);
void	check_args(int ac, char **av, t_parser *parser);
int		is_identifier(char *line, char *id);
char	*extract_value(char *line);
void	exit_texture_error(const char *direction);
void	validate_single_texture(const char *path, const char *direction);
void	validate_textures(t_map_data *map);

// file parsing
void	read_map_lines(char *line, t_map_data *map_data, int fd);
void	copy_file_blindly(t_main *main);
void	parse_colours(t_map_data *map, t_parser *parser);
void	parse(int ac, char **av, t_main *main);

// initialisation
t_main	*initialise(void);
int		is_only_num(char *s);
int		store_identifier(char *line, t_map_data *map_data, t_parser *parser);
int		is_player_char(char c);
int		get_row_length(char *row);
void	get_height_and_length(t_map_data *map);

// check map
void	validate_map(t_map_data *map_data);
int		is_map_line(char *line);
int		is_valid_map_char(char c);
int		line_is_valid(char *line);
int		make_map(char *line, t_map_data *map);
char	**make_map_copy(char **map, int height);
void	free_map_copy(char **copy);
void	flood_error(void);
int		is_out_of_bounds(t_flood *f, int x, int y);
void	floodfill(t_flood *f, int x, int y);

#endif