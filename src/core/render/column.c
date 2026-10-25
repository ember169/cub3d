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

/* wall_x = ou le rayon touche le mur, dans [0, 1). Retournement (7.9) pour
** lire la texture de gauche a droite vu du joueur (inverse de lodev, car
** ici y va vers le Sud). tex_pos != 0 quand le mur depasse l'ecran */
static void	col_texture(t_game *g, t_ray *r, t_col *c)
{
	double	wall_x;

	c->tex = select_texture(g, r);
	if (r->hit_side == 0)
		wall_x = g->pl.pos.y + r->perp * r->dir.y;
	else
		wall_x = g->pl.pos.x + r->perp * r->dir.x;
	wall_x -= floor(wall_x);
	c->tex_x = (int)(wall_x * c->tex->w);
	if (c->tex_x >= c->tex->w)
		c->tex_x = c->tex->w - 1;
	if ((r->hit_side == 0 && r->dir.x < 0)
		|| (r->hit_side == 1 && r->dir.y > 0))
		c->tex_x = c->tex->w - 1 - c->tex_x;
	c->step = (double)c->tex->h / c->line_h;
	c->tex_pos = (c->start - WIN_H / 2 + c->line_h / 2) * c->step;
}

/* Une seule passe : chaque pixel est ecrit une fois (plafond, mur, sol) */
void	draw_column(t_game *g, t_ray *r, int x)
{
	t_col	c;
	int		y;
	int		color;

	c.x = x;
	col_bounds(&c, r->perp);
	col_texture(g, r, &c);
	y = 0;
	while (y < WIN_H)
	{
		if (y < c.start)
			color = g->sc.ceil;
		else if (y > c.end)
			color = g->sc.floor;
		else
		{
			color = get_texel(c.tex, c.tex_x, (int)c.tex_pos);
			c.tex_pos += c.step;
		}
		put_pixel(&g->frame, x, y, color);
		y++;
	}
}
