/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Textures (G3) a charger entre mlx_init et la fenetre */
void	gfx_init(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_game(g, 1, E_MLX);
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, WIN_TITLE);
	if (!g->win)
		exit_game(g, 1, E_MLX);
	g->frame.ptr = mlx_new_image(g->mlx, WIN_W, WIN_H);
	if (!g->frame.ptr)
		exit_game(g, 1, E_MLX);
	g->frame.addr = mlx_get_data_addr(g->frame.ptr, &g->frame.bpp,
			&g->frame.line_len, &g->frame.endian);
	g->frame.w = WIN_W;
	g->frame.h = WIN_H;
}
