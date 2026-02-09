/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:27:24 by amarquez          #+#    #+#             */
/*   Updated: 2026/02/03 18:27:26 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static t_identifier	check_identifier(char *line, t_game *game)
{
	if (*line == '1' || *line == '0')
		exit_error(ERR_MISSPLACED_MAP, game);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (NORTH_TEXTURE);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (WEST_TEXTURE);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (SOUTH_TEXTURE);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (EAST_TEXTURE);
	if (ft_strncmp(line, "C", 1) == 0)
		return (CEILING_COLOR);
	if (ft_strncmp(line, "F", 1) == 0)
		return (FLOOR_COLOR);
	else
		return (-1);
}

static void	fill_info(t_game *game)
{
	t_identifier	id;
	char			*line;

	line = game->config_line;
	while (*line && is_whitespace(*line))
		line++;
	if (!*line || *line == '\n')
		return ;
	id = check_identifier(line, game);
	if (id >= NORTH_TEXTURE && id <= WEST_TEXTURE)
		parse_texture(game, line + 2, id);
	else if (id == FLOOR_COLOR || id == CEILING_COLOR)
		parse_colors(game, line + 1, id);
	else
		exit_error(ERR_WRONG_ID, game);
}

void	parse_info(t_game *game)
{
	char	*map_str;

	map_str = NULL;
	game->config_line = get_next_line(game->config_fd);
	while (game->config_line)
	{
		if (!is_line_empty(game->config_line) && game->info_filled < 6)
			fill_info(game);
		else if (!is_line_empty(game->config_line) && game->info_filled == 6)
			map_str = parse_map_line(game, map_str);
		free(game->config_line);
		game->config_line = get_next_line(game->config_fd);
	}
	parse_map(game, map_str);
	free(map_str);
	load_textures(game);
}
