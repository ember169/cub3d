/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** TEMP : remplacant minimal de M1/M2 (A) pour tester le rendu a la main.
** Memes prototypes que le contrat : quand core/move/ arrive, retirer ce
** fichier des SRCS (sinon le lien echoue : symboles en double).
*/

/* TEMP */
double	now_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

/* TEMP : rotation de dir ET plane, avec old pour ne pas deformer */
static void	temp_rotate(t_player *p, double a)
{
	double	old;

	old = p->dir.x;
	p->dir.x = p->dir.x * cos(a) - p->dir.y * sin(a);
	p->dir.y = old * sin(a) + p->dir.y * cos(a);
	old = p->plane.x;
	p->plane.x = p->plane.x * cos(a) - p->plane.y * sin(a);
	p->plane.y = old * sin(a) + p->plane.y * cos(a);
}

/* TEMP : collision axe par axe, sans marge */
static void	temp_move(t_game *g, double dx, double dy)
{
	if (!is_solid(g, (int)(g->pl.pos.x + dx), (int)g->pl.pos.y))
		g->pl.pos.x += dx;
	if (!is_solid(g, (int)g->pl.pos.x, (int)(g->pl.pos.y + dy)))
		g->pl.pos.y += dy;
}

/* TEMP : W/S = avant/arriere selon dir, A/D = pas de cote selon plane */
void	update_player(t_game *g, double dt)
{
	double	fwd;
	double	side;
	double	rot;
	double	len;

	rot = (g->keys[K_RIGHT] - g->keys[K_LEFT]) * ROT_SPEED * dt;
	if (rot != 0)
		temp_rotate(&g->pl, rot);
	fwd = (g->keys[K_W] - g->keys[K_S]) * MOVE_SPEED * dt;
	side = (g->keys[K_D] - g->keys[K_A]) * MOVE_SPEED * dt;
	len = sqrt(g->pl.plane.x * g->pl.plane.x + g->pl.plane.y * g->pl.plane.y);
	temp_move(g, g->pl.dir.x * fwd + g->pl.plane.x / len * side,
		g->pl.dir.y * fwd + g->pl.plane.y / len * side);
}
