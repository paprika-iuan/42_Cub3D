/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:31:49 by jgirbau-          #+#    #+#             */
/*   Updated: 2026/02/01 17:07:55 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/*Loop func that will will render the '3d' view of the project.*/
static void	ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_memset(game->img->pixels, 0,
		game->img->width * game->img->height * 4);
	game->i = 0;
	init_ray(game);
	(void)param;
}

static void	key_hooks(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	move_player(keydata, game);
}

/*Sets the initial position of the player.*/
void	player_start(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = (float)x + 0.5f;
				game->player.y = (float)y + 0.5f;
				set_player_dir(game, c);
				break ;
			}
			x++;
		}
		y++;
	}
}

int	run_render(t_game *game)
{
	player_start(game);
	game->mlx = mlx_init(game->screen_w, game->screen_h, "Cub3D", false);
	if (!game->mlx)
		exit_error((char *)mlx_strerror(mlx_errno), game);
	game->img = mlx_new_image(game->mlx, game->screen_w, game->screen_h);
	if (!game->img)
		exit_error((char *)mlx_strerror(mlx_errno), game);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		exit_error((char *)mlx_strerror(mlx_errno), game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_key_hook(game->mlx, key_hooks, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (1);
}
