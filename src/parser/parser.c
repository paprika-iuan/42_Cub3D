/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:28:01 by amarquez          #+#    #+#             */
/*   Updated: 2026/02/03 18:28:02 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static void	init_textures(t_game *game)
{
	int	i;

	game->textures.n = NULL;
	game->textures.w = NULL;
	game->textures.e = NULL;
	game->textures.s = NULL;
	game->textures.floor = EMPTY_COLOR;
	game->textures.sky = EMPTY_COLOR;
	i = -1;
	while (++i < 4)
		game->wall_paths[i] = NULL;
}

static void	init_structs(t_game *game)
{
	game->mlx = NULL;
	game->img = NULL;
	game->player.x = 0;
	game->player.y = 0;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.6f;
	game->map = NULL;
	game->i = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->screen_w = SCREEN_WIDTH;
	game->screen_h = SCREEN_HEIGHT;
	game->info_filled = 0;
	game->player_found = 0;
	game->config_fd = -1;
	game->config_line = NULL;
	init_textures(game);
}

int	validate_file(char **argv, t_game *game)
{
	int	len;
	int	fd;

	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strcmp(argv[1] + len - 4, ".cub") != 0)
		exit_error(ERR_INVALID_EXTENSION, game);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
			exit_error(ERR_FILE_NOT_FOUND, game);
		else if (errno == EACCES)
			exit_error(ERR_FILE_ACCESS, game);
		else
			exit_error(ERR_OPEN_FILE, game);
	}
	return (fd);
}

void	parser(t_game *game, char **argv)
{
	init_structs(game);
	game->config_fd = validate_file(argv, game);
	parse_info(game);
	close(game->config_fd);
}
