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

/* Chaque texture garde sa propre taille : ne pas supposer 64x64 */
static void	load_texture(t_game *g, int i)
{
	t_img	*t;

	t = &g->tex[i];
	t->ptr = mlx_xpm_file_to_image(g->mlx, g->sc.tex_path[i], &t->w, &t->h);
	if (!t->ptr)
		exit_game(g, 1, E_TEXLOAD);
	t->addr = mlx_get_data_addr(t->ptr, &t->bpp, &t->line_len, &t->endian);
}

/* Textures avant la fenetre : une texture invalide ne fait rien clignoter */
void	gfx_init(t_game *g)
{
	int	i;

	g->mlx = mlx_init();
	if (!g->mlx)
		exit_game(g, 1, E_MLX);
	i = 0;
	while (i < 4)
		load_texture(g, i++);
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
