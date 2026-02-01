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
# include "libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# define TILE_SIZE 64
# define MOVE_SPEED 0.1f
# define ROT_SPEED 0.05f

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
	int			map_width;
	int			map_height;
	int			screen_w;
	int			screen_h;
	int			i;
}	t_game;

//////rend_main.c
int			run_render(t_game *game);
void		player_start(t_game *game);

//////rend_exit.c
void		ft_error(void);
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
