/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:07:32 by jgirbau-          #+#    #+#             */
/*   Updated: 2026/02/01 16:36:38 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

// void	ft_error(void)
// {
// 	// CANVIAR
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

void	free_textures(t_game *game)
{
	if (game->textures.n)
		mlx_delete_texture(game->textures.n);
	if (game->textures.s)
		mlx_delete_texture(game->textures.s);
	if (game->textures.e)
		mlx_delete_texture(game->textures.e);
	if (game->textures.w)
		mlx_delete_texture(game->textures.w);
}
