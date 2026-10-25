/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Dessine dans g->frame sans l'afficher : game_loop fait le put_image
** (en bonus, sprites et minimap s'intercalent entre les deux) */
void	render_frame(t_game *g)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		cast_ray(g, x, &r);
		draw_column(g, &r, x);
		if (g->zbuf)
			g->zbuf[x] = r.perp;
		x++;
	}
}
