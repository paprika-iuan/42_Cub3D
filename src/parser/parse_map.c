/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:15:16 by amarquez          #+#    #+#             */
/*   Updated: 2026/02/02 16:15:18 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static void	validate_map_line(t_game *game, char *line, char *map_str)
{
	int	i;
	int	line_length;

	i = 0;
	line_length = 0;
	while (line[i])
	{
		if ((line[i] != '0' && line[i] != '1' && line[i] != 'N'
				&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
				&& line[i] != ' ' && line[i] != '\n'))
		{
			free(map_str);
			exit_error(ERR_INVALID_CHAR, game);
		}
		if (line[i] != '\n')
			line_length++;
		i++;
	}
	game->map_height++;
	if (line_length > game->map_width)
		game->map_width = line_length;
}

static char	*fill_row(char **map_split, int i, int map_width)
{
	char	*row;
	int		j;
	int		line_len;

	row = (char *)malloc(sizeof(char) * (map_width + 1));
	if (!row)
		return (NULL);
	j = 0;
	line_len = ft_strlen(map_split[i]);
	while (j < map_width)
	{
		if (j >= line_len || map_split[i][j] == ' ')
			row[j] = '1';
		else
			row[j] = map_split[i][j];
		j++;
	}
	row[j] = '\0';
	return (row);
}

char	**copy_map(char **map_split, t_game *game, char *map_str)
{
	int		i;
	char	**map;

	map = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!map)
	{
		free(map_str);
		exit_error(ERR_MALLOC, game);
	}
	i = 0;
	while (i < game->map_height)
	{
		map[i] = fill_row(map_split, i, game->map_width);
		if (!map[i])
		{
			free(map_str);
			free_matrix(map);
			exit_error(ERR_MALLOC, game);
		}
		i++;
	}
	map[i] = NULL;
	free_matrix(map_split);
	validate_map(map, game, map_str);
	return (map);
}

char	*parse_map_line(t_game *game, char *map_str)
{
	char	*temp;

	if (game->info_filled != 6)
	{
		free(map_str);
		exit_error(ERR_MISSING_ID, game);
	}
	validate_map_line(game, game->config_line, map_str);
	temp = ft_strjoin(map_str, game->config_line);
	if (!temp)
	{
		free(map_str);
		exit_error(ERR_MALLOC, game);
	}
	free(map_str);
	return (temp);
}

void	parse_map(t_game *game, char *map_str)
{
	char	**map_split;
	char	**map;

	map_split = ft_split(map_str, '\n');
	if (!map_split)
	{
		free(map_str);
		exit_error(ERR_MALLOC, game);
	}
	map = copy_map(map_split, game, map_str);
	game->map = map;
}
