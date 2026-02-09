/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:29:00 by amarquez          #+#    #+#             */
/*   Updated: 2026/02/03 18:29:01 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static int	is_end_of_color(const char *line)
{
	while (*line && *line != '\n')
	{
		if (!is_whitespace(*line))
			return (0);
		line++;
	}
	return (1);
}

static int	parse_single_color(char **line)
{
	int	color;

	color = 0;
	if (!ft_safe_atoi(*line, &color))
		return (-1);
	if (color < 0 || color > 255)
		return (-1);
	while (ft_isdigit(**line))
		(*line)++;
	if (**line == ',')
	{
		(*line)++;
		if (!ft_isdigit(**line))
			return (-1);
	}
	else if (!is_end_of_color(*line))
		return (-1);
	return (color);
}

static int	get_color(char *line, uint32_t *color)
{
	int	red;
	int	green;
	int	blue;

	red = parse_single_color(&line);
	if (red < 0)
		return (0);
	green = parse_single_color(&line);
	if (green < 0)
		return (0);
	blue = parse_single_color(&line);
	if (blue < 0)
		return (0);
	*color = red << 24 | green << 16 | blue << 8 | 0xFF;
	return (1);
}

void	parse_colors(t_game *game, char *line, t_identifier id)
{
	uint32_t	color;

	if ((game->textures.sky && id == CEILING_COLOR)
		|| (game ->textures.floor && id == FLOOR_COLOR))
		exit_error(ERR_DUP_ID, game);
	if (!is_whitespace(*line))
		exit_error(ERR_NO_SPACE, game);
	while (is_whitespace(*line))
		line++;
	if (!*line || *line == '\n')
		exit_error(ERR_NO_COLOR, game);
	if (!get_color(line, &color))
		exit_error(ERR_COLOR_PARSE, game);
	if (id == CEILING_COLOR)
		game->textures.sky = color;
	else if (id == FLOOR_COLOR)
		game->textures.floor = color;
	game->info_filled++;
}
