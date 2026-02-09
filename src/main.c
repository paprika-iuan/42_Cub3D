/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:45:30 by jgirbau-          #+#    #+#             */
/*   Updated: 2026/02/01 17:41:53 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	free_wall_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(game->wall_paths[i]);
		i++;
	}
}

void	exit_error(char *msg, t_game *game)
{
	if (game)
	{
		if (game->config_line)
		{
			while (game->config_line)
			{
				free(game->config_line);
				game->config_line = get_next_line(game->config_fd);
			}
		}
		close(game->config_fd);
		free_wall_paths(game);
		free_textures(game);
		if (game->map)
			free_matrix(game->map);
		free(game);
	}
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	else
		ft_putstr_fd(ERR_UNKNOWN, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		exit_error(ERR_USAGE, NULL);
	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	parser(game, argv);
	run_render(game);
	free_wall_paths(game);
	free_textures(game);
	free_matrix(game->map);
	free(game);
	return (EXIT_SUCCESS);
}
