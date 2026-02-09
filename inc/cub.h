/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:26:18 by jgirbau-          #+#    #+#             */
/*   Updated: 2026/02/01 17:39:23 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <string.h>
# include <sys/time.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# define TILE_SIZE 64
# define MOVE_SPEED 0.1f
# define ROT_SPEED 0.05f
# define SCREEN_HEIGHT 600
# define SCREEN_WIDTH 800
# define EMPTY_COLOR 0x00000000

// Error messages
# define ERR_USAGE "Usage: ./cub3d <config_file.cub>\n"
# define ERR_INVALID_EXTENSION "Invalid .cub file extension\n"
# define ERR_FILE_NOT_FOUND ".cub file does not exist\n"
# define ERR_FILE_ACCESS "Permission denied for .cub file\n"
# define ERR_OPEN_FILE "Cannot open .cub file\n"
# define ERR_MISSPLACED_MAP "Map must be placed at the end of file\n"
# define ERR_WRONG_ID "Unknown identifier\n"
# define ERR_DUP_ID "Duplicate identifier\n"
# define ERR_MISSING_ID "Missing identifier\n"
# define ERR_NO_SPACE "Identifier must be followed by whitespace\n"
# define ERR_WRONG_IMG_EXT "Texture must be a .png file\n"
# define ERR_NO_IMG_FILE "No texture path\n"
# define ERR_TEXT_LOAD "Texture loading failed\n"
# define ERR_TEXT_NOT_FOUND "Texture file does not exist\n"
# define ERR_TEXT_ACCESS "Permission denied for texture file\n"
# define ERR_OPEN_TEXT "Cannot open texture file\n"
# define ERR_NO_COLOR "No color info\n"
# define ERR_COLOR_PARSE "Color could not be parsed\n"
# define ERR_INVALID_CHAR "Invalid character found in map\n"
# define ERR_MAP_NOT_CLOSED "Map is not closed/surrounded by walls\n"
# define ERR_NO_PLAYER "No player starting position found\n"
# define ERR_MULTIPLE_PLAYERS "Multiple player starting positions found\n"
# define ERR_MALLOC "Malloc allocation failed\n"
# define ERR_UNKNOWN "Unknown failure\n" 

typedef enum e_identifier
{
	NORTH_TEXTURE = 0,
	SOUTH_TEXTURE = 1,
	EAST_TEXTURE = 2,
	WEST_TEXTURE = 3,
	FLOOR_COLOR = 4,
	CEILING_COLOR = 5,
	INVALID = -1,
}	t_identifier;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_player;

typedef struct s_pos
{
	int		map_x;
	int		map_y;
	float	raydir_x;
	float	raydir_y;
	float	delta_x;
	float	delta_y;
	float	side_x;
	float	side_y;
	float	step_x;
	float	step_y;
	float	perpwalldist;
	int		hit;
	int		side;
	float	wall_x;
	int		tex_x;
}	t_pos;

typedef struct s_texture
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*e;
	mlx_texture_t	*w;
	uint32_t		floor;
	uint32_t		sky;
}	t_texture;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_pos		p;
	t_texture	textures;
	char		**map;
	char		*wall_paths[4];
	int			info_filled;
	int			map_width;
	int			map_height;
	int			screen_w;
	int			screen_h;
	int			i;
	int			config_fd;
	char		*config_line;
	char		*map_str;
	int			player_found;
}	t_game;

//////main.c
void		exit_error(char *msg, t_game *game);

//////parser.c
void		parser(t_game *game, char **argv);

//////parse_info.c
void		parse_info(t_game *game);

//////parse_textures.c
void		load_textures(t_game *game);
void		parse_texture(t_game *game, char *line, t_identifier id);

//////parse_colors.c
void		parse_colors(t_game *game, char *line, t_identifier id);

//////parse_map.c
char		*parse_map_line(t_game *game, char *map_str);
void		parse_map(t_game *game, char *map_str);

//////validate_map.c
void	validate_map(char **map, t_game *game, char *map_str);

//////rend_main.c
int			run_render(t_game *game);
void		player_start(t_game *game);

//////rend_exit.c
void		free_textures(t_game *game);

//////rend_move.c
void		move_player(mlx_key_data_t keydata, t_game *game);
void		set_player_dir(t_game *game, char c);
void		check_colision(t_game *game, float new_x, float new_y);

//////rend_pos.c
void		init_ray(t_game *game);

//////rend_3d.c
void		draw_vertical_line(t_game *game, t_pos *p);
void		calculate_texture_x(t_game *game, t_pos *p);

//////rend_texture.c
void		calculate_texture_x(t_game *game, t_pos *p);
uint32_t	pixel_tex_color(t_game *game, int y, int l_h, int draw_start);

#endif
