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

/* Une seule passe : chaque pixel est ecrit une fois (plafond, mur, sol).
** Couleur unie selon hit_side pour voir le relief ; R5 met la texture */
void	draw_column(t_game *g, t_ray *r, int x)
{
	t_col	c;
	int		y;
	int		color;

	c.x = x;
	col_bounds(&c, r->perp);
	y = 0;
	while (y < WIN_H)
	{
		if (y < c.start)
			color = g->sc.ceil;
		else if (y > c.end)
			color = g->sc.floor;
		else if (r->hit_side == 0)
			color = 0xC0C0C0;
		else
			color = 0x808080;
		put_pixel(&g->frame, x, y, color);
		y++;
	}
}
