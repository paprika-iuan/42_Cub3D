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

// static void	load_textures(t_game *game)
// {
// 	game->textures.n = mlx_load_png("./textures/north.png");
// 	game->textures.s = mlx_load_png("./textures/south.png");
// 	game->textures.e = mlx_load_png("./textures/east.png");
// 	game->textures.w = mlx_load_png("./textures/west.png");
// 	if (!game->textures.n || !game->textures.s
// 		|| !game->textures.e || !game->textures.w)
// 	{
// 		ft_putstr_fd("Textura mal. Tete! Espabila!\n", 2);
// 		exit(1);
// 	}
// 	game->textures.floor = 0x808080FF;
// 	game->textures.sky = 0x87CEEBFF;
// }

// static void	init_structs(t_game *game)
// {
// 	static char	*map[] = {
// 	"11111111",
// 	"10000001",
// 	"10000001",
// 	"100S0001",
// 	"10000001",
// 	"10010001",
// 	"11111111",
// 	NULL
// 	};

// 	game->mlx = NULL;
// 	game->img = NULL;
// 	game->player.x = 0;
// 	game->player.y = 0;
// 	game->player.dir_x = 0;
// 	game->player.dir_y = 0;
// 	game->player.plane_x = 0;
// 	game->player.plane_y = 0.6f;
// 	game->map = map;
// 	game->i = 0;
// 	game->map_width = 8;
// 	game->map_height = 7;
// 	game->screen_w = 800;
// 	game->screen_h = 600;
// 	load_textures(game);
// }

int	main(int argc, char **argv)
{
	t_game	*game;

	validate_args(argc, argv);
	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	// init_structs(game);
	// run_render(game);
	// free_textures(game);
	free(game);
	return (EXIT_SUCCESS);
}
