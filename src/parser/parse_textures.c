/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:28:33 by amarquez          #+#    #+#             */
/*   Updated: 2026/02/03 18:28:35 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	load_textures(t_game *game)
{
	game->textures.n = mlx_load_png(game->wall_paths[NORTH_TEXTURE]);
	game->textures.s = mlx_load_png(game->wall_paths[SOUTH_TEXTURE]);
	game->textures.e = mlx_load_png(game->wall_paths[EAST_TEXTURE]);
	game->textures.w = mlx_load_png(game->wall_paths[WEST_TEXTURE]);
	if (!game->textures.n || !game->textures.s
		|| !game->textures.e || !game->textures.w)
		exit_error(ERR_TEXT_LOAD, game);
}

static void	check_image_extension(char *path, int len, t_game *game)
{
	if (len < 4 || ft_strcmp(path + len - 4, ".png") != 0)
	{
		free(path);
		exit_error(ERR_WRONG_IMG_EXT, game);
	}
}

static void	check_img_path(char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		if (errno == ENOENT)
			exit_error(ERR_TEXT_NOT_FOUND, game);
		else if (errno == EACCES)
			exit_error(ERR_TEXT_ACCESS, game);
		else
			exit_error(ERR_OPEN_TEXT, game);
	}
	close(fd);
}

static char	*extract_texture_path(char *line, t_game *game)
{
	int		len;
	char	*path;

	len = ft_strlen(line);
	while (len > 0 && (is_whitespace(line[len - 1]) || line[len - 1] == '\n'))
		len--;
	path = ft_strndup(line, len);
	if (!path)
		exit_error(ERR_MALLOC, game);
	check_image_extension(path, len, game);
	check_img_path(path, game);
	return (path);
}

void	parse_texture(t_game *game, char *line, t_identifier id)
{
	char	*path;

	if (game->wall_paths[id])
		exit_error(ERR_DUP_ID, game);
	if (!is_whitespace(*line))
		exit_error(ERR_NO_SPACE, game);
	while (is_whitespace(*line))
		line++;
	if (!*line || *line == '\n')
		exit_error(ERR_NO_IMG_FILE, game);
	path = extract_texture_path(line, game);
	game->wall_paths[id] = path;
	game->info_filled++;
}
