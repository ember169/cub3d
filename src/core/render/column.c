/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Un mur de hauteur 1 a distance 1 remplit l'ecran. perp >= MIN_PERP,
** donc pas de division par 0 ; start et end sont ramenes dans l'ecran */
static void	col_bounds(t_col *c, double perp)
{
	c->line_h = (int)(WIN_H / perp);
	c->start = WIN_H / 2 - c->line_h / 2;
	if (c->start < 0)
		c->start = 0;
	c->end = WIN_H / 2 + c->line_h / 2;
	if (c->end >= WIN_H)
		c->end = WIN_H - 1;
}

/* A completer (R4) : plafond au-dessus de start, sol sous end, couleur
** selon hit_side ; R5 remplacera la couleur unie par la texture */
void	draw_column(t_game *g, t_ray *r, int x)
{
	t_col	c;
	int		y;

	c.x = x;
	col_bounds(&c, r->perp);
	y = c.start;
	while (y <= c.end)
		put_pixel(&g->frame, x, y++, 0xFFFFFF);
}
