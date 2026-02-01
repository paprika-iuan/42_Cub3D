/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:35:15 by jgirbau-          #+#    #+#             */
/*   Updated: 2026/02/01 17:30:31 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/*The functions in this file chech ad update all the variables that determine
the position of the player and if it has hit a wall.*/

static float	set_delta(float dir)
{
	if (dir == 0)
		return (1e30);
	else
		return (fabs(1 / dir));
}

/*First we calculate the perpendicular distance from the player to the wall, 
then the exact decimal point of the wall where the ray hit: this will be
especially helpful when applying textures to the wall.*/

static void	calc_wall_dist(t_game *game, t_pos *p)
{
	if (p->side == 0)
		p->perpwalldist = p->side_x - p->delta_x;
	else
		p->perpwalldist = p->side_y - p->delta_y;
	if (p->side == 0)
		p->wall_x = game->player.y + p->perpwalldist * p->raydir_y;
	else
		p->wall_x = game->player.x + p->perpwalldist * p->raydir_x;
	p->wall_x -= floor(p->wall_x);
}

/*Here we check where the raycaster hit the wall (if it does). We step through
the map grid until finding a wall, updating position and side at each step.*/
static void	check_hit(t_game *game, t_pos *p)
{
	p->hit = 0;
	while (p->hit == 0)
	{
		if (p->side_x < p->side_y)
		{
			p->side_x += p->delta_x;
			p->map_x += p->step_x;
			p->side = 0;
		}
		else
		{
			p->side_y += p->delta_y;
			p->map_y += p->step_y;
			p->side = 1;
		}
		if (p->map_y >= 0 && p->map_y < game->map_height
			&& p->map_x >= 0 && p->map_x < game->map_width
			&& game->map[p->map_y][p->map_x] == '1')
			p->hit = 1;
	}
}

/*Define which direction the ray is cast, and the distance that
separates the player from next grid line in each axis.*/
static void	set_stepside(t_game *game, t_pos *p)
{
	if (p->raydir_x < 0.0f)
	{
		p->step_x = -1;
		p->side_x = (game->player.x - p->map_x) * p->delta_x;
	}
	else
	{
		p->step_x = 1;
		p->side_x = (p->map_x + 1.0f - game->player.x) * p->delta_x;
	}
	if (p->raydir_y < 0.0f)
	{
		p->step_y = -1;
		p->side_y = (game->player.y - p->map_y) * p->delta_y;
	}
	else
	{
		p->step_y = 1;
		p->side_y = (p->map_y + 1.0f - game->player.y) * p->delta_y;
	}
}

/*Function that will make the necessary calculations before rendering the '3d'
view from the player perspective by raycasting. Casts one ray per screen 
column and calls draw_vertical_line to render each column.*/
void	init_ray(t_game *game)
{
	float	camera_x;
	t_pos	*p;

	p = &game->p;
	while (game->i < game->screen_w)
	{
		camera_x = 2 * game->i / (float)game->screen_w - 1;
		p->raydir_x = game->player.dir_x + game->player.plane_x * camera_x;
		p->raydir_y = game->player.dir_y + game->player.plane_y * camera_x;
		p->map_x = (int)game->player.x;
		p->map_y = (int)game->player.y;
		p->delta_x = set_delta(p->raydir_x);
		p->delta_y = set_delta(p->raydir_y);
		set_stepside(game, p);
		check_hit(game, p);
		calc_wall_dist(game, p);
		draw_vertical_line(game, p);
		game->i++;
	}
}
