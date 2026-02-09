/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:09:57 by amarquez          #+#    #+#             */
/*   Updated: 2026/02/09 12:09:59 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static void	check_player_count(int player_count, char **map,
				char *map_str, t_game *game)
{
	if (player_count == 0)
	{
		free(map_str);
		free_matrix(map);
		exit_error(ERR_NO_PLAYER, game);
	}
	if (player_count > 1)
	{
		free(map_str);
		free_matrix(map);
		exit_error(ERR_MULTIPLE_PLAYERS, game);
	}
}

static void	validate_player_pos(char **map, t_game *game, char *map_str)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	check_player_count(player_count, map, map_str, game);
}

static void	validate_map_edges(char **map, t_game *game, char *map_str)
{
	int	i;
	int	j;
	int	valid;

	i = 0;
	valid = 1;
	while (i < game->map_width)
	{
		if (map[0][i] != '1' || map[game->map_height - 1][i] != '1')
			valid = 0;
		i++;
	}
	j = 0;
	while (j < game->map_height)
	{
		if (map[j][0] != '1' || map[j][game->map_width - 1] != '1')
			valid = 0;
		j++;
	}
	if (!valid)
	{
		free(map_str);
		free_matrix(map);
		exit_error(ERR_MAP_NOT_CLOSED, game);
	}
}

void	validate_map(char **map, t_game *game, char *map_str)
{
	validate_player_pos(map, game, map_str);
	validate_map_edges(map, game, map_str);
}
