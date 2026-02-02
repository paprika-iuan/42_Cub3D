/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:06:03 by jgirbau-          #+#    #+#             */
/*   Updated: 2026/02/01 17:05:59 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/*In this function we rotate the player direction and the plane. This way, when
 the player rotates , in association with the keys 'a' and 'd', both it and 
 the FOV rotates.*/

static void	rotate_ad(t_game *game, float angle)
{
	float	dir_x;
	float	dir_y;
	float	pla_x;
	float	pla_y;

	dir_x = game->player.dir_x * cosf(angle) - game->player.dir_y * sinf(angle);
	dir_y = game->player.dir_x * sinf(angle) + game->player.dir_y * cosf(angle);
	pla_x = game->player.plane_x * cosf(angle)
		- game->player.plane_y * sinf(angle);
	pla_y = game->player.plane_x * sinf(angle)
		+ game->player.plane_y * cosf(angle);
	game->player.dir_x = dir_x;
	game->player.dir_y = dir_y;
	game->player.plane_x = pla_x;
	game->player.plane_y = pla_y;
}

/*Binds wasd to the player movement.*/
void	move_player(mlx_key_data_t keydata, t_game *game)
{
	float	new_x;
	float	new_y;

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		new_x = game->player.x;
		new_y = game->player.y;
		if (keydata.key == MLX_KEY_W)
		{
			new_x += game->player.dir_x * MOVE_SPEED;
			new_y += game->player.dir_y * MOVE_SPEED;
		}
		if (keydata.key == MLX_KEY_S)
		{
			new_x -= game->player.dir_x * MOVE_SPEED;
			new_y -= game->player.dir_y * MOVE_SPEED;
		}
		if (keydata.key == MLX_KEY_A)
			rotate_ad(game, ROT_SPEED);
		if (keydata.key == MLX_KEY_D)
			rotate_ad(game, -ROT_SPEED);
		check_colision(game, new_x, new_y);
	}
}

static void	dir_ew(t_game *game, char c)
{
	if (c == 'E')
	{
		game->player.dir_x = 1.0f;
		game->player.dir_y = 0.0f;
		game->player.plane_x = 0.0f;
		game->player.plane_y = 0.66f;
	}
	if (c == 'W')
	{
		game->player.dir_x = -1.0f;
		game->player.dir_y = 0.0f;
		game->player.plane_x = 0.0f;
		game->player.plane_y = -0.66f;
	}
}

/*Orients the player in the direction specified by the map*/
void	set_player_dir(t_game *game, char c)
{
	if (c == 'N')
	{
		game->player.dir_x = 0.0f;
		game->player.dir_y = -1.0f;
		game->player.plane_x = 0.66f;
		game->player.plane_y = 0.0f;
	}
	if (c == 'S')
	{
		game->player.dir_x = 0.0f;
		game->player.dir_y = 1.0f;
		game->player.plane_x = 0.66f;
		game->player.plane_y = 0.0f;
	}
	else
		dir_ew(game, c);
}

/*Checks if the player has hit a wall.*/
void	check_colision(t_game *game, float new_x, float new_y)
{
	int	mx;
	int	my;

	mx = (int)new_x;
	my = (int)new_y;
	if (my >= 0 && game->map[my] != NULL
		&& mx >= 0 && mx < (int)ft_strlen(game->map[my])
		&& game->map[my][mx] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}
