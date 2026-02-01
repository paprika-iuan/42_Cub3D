/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:23:46 by jgirbau-          #+#    #+#             */
/*   Updated: 2026/02/01 17:36:47 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/*We paint the sky vertically whatever is from y zero until we hit a wall
(draw_start)*/
static void	draw_sky(t_game *game, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(game->img, game->i, y, game->textures.sky);
		y++;
	}
}

/*Same as in the previous function, we paint the floor vertcally whatever pixel
is further than the end of the wall until the end of the program window.*/
static void	draw_floor(t_game *game, int draw_end)
{
	int	y;

	y = draw_end + 1;
	while (y < game->screen_h)
	{
		mlx_put_pixel(game->img, game->i, y, game->textures.floor);
		y++;
	}
}

/*Paints each wall pixel by pixel, befor painting checks the color texture
associated to the pixel position and paints it accordingly.*/
static void	draw_wall(t_game *game, int d_start, int d_end, int line_h)
{
	int			y;
	uint32_t	color;

	y = d_start;
	while (y <= d_end)
	{
		color = pixel_tex_color(game, y, line_h, d_start);
		mlx_put_pixel(game->img, game->i, y, color);
		y++;
	}
}

/*From a bucle. Renders one line of the view from the layer position and it
paints it according to the color associated to the floor, sky or wall texture.*/
void	draw_vertical_line(t_game *game, t_pos *p)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(game->screen_h / p->perpwalldist);
	draw_start = -line_height / 2 + game->screen_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->screen_h / 2;
	if (draw_end >= game->screen_h)
		draw_end = game->screen_h - 1;
	calculate_texture_x(game, p);
	draw_sky(game, draw_start);
	draw_wall(game, draw_start, draw_end, line_height);
	draw_floor(game, draw_end);
}
