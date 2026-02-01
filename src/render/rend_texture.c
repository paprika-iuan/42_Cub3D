/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 17:30:32 by jgirbau-          #+#    #+#             */
/*   Updated: 2026/02/01 17:38:53 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/*Selects the correct texture based on which wall side was hit.*/
static mlx_texture_t	*select_texture(t_game *game, t_pos *p)
{
	if (p->side == 0)
	{
		if (p->raydir_x > 0)
			return (game->textures.e);
		else
			return (game->textures.w);
	}
	else
	{
		if (p->raydir_y > 0)
			return (game->textures.s);
		else
			return (game->textures.n);
	}
}

/*Calculates which column of the texture to use based on where the ray hit.*/
void	calculate_texture_x(t_game *game, t_pos *p)
{
	mlx_texture_t	*tex;

	tex = select_texture(game, p);
	p->tex_x = (int)(p->wall_x * (double)tex->width);
	if (p->side == 0 && p->raydir_x > 0)
		p->tex_x = tex->width - p->tex_x - 1;
	if (p->side == 1 && p->raydir_y < 0)
		p->tex_x = tex->width - p->tex_x - 1;
}

/*Extracts the color from a specific pixel in the texture.*/
static uint32_t	get_pixel_color(mlx_texture_t *tex, int x, int y)
{
	int			index;
	uint32_t	color;

	index = (tex->width * y + x) * 4;
	color = (tex->pixels[index] << 24)
		| (tex->pixels[index + 1] << 16)
		| (tex->pixels[index + 2] << 8)
		| tex->pixels[index + 3];
	return (color);
}

/*Calculates the texture color for a specific screen pixel.*/
uint32_t	pixel_tex_color(t_game *game, int y, int l_h, int draw_start)
{
	mlx_texture_t	*tex;
	int				tex_y;
	double			step;
	double			tex_pos;
	uint32_t		color;

	tex = select_texture(game, &game->p);
	step = 1.0 * tex->height / l_h;
	tex_pos = (draw_start - game->screen_h / 2 + l_h / 2) * step;
	tex_pos += (y - draw_start) * step;
	tex_y = (int)tex_pos & (tex->height - 1);
	color = get_pixel_color(tex, game->p.tex_x, tex_y);
	if (game->p.side == 1)
		color = (color >> 1) & 0x7F7F7F7F;
	return (color);
}
