/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Rotation 2D de dir ET plane ; old garde dir.x avant qu'il soit ecrase */
void	rotate_player(t_player *p, double a)
{
	double	c;
	double	s;
	double	old;

	c = cos(a);
	s = sin(a);
	old = p->dir.x;
	p->dir.x = p->dir.x * c - p->dir.y * s;
	p->dir.y = old * s + p->dir.y * c;
	old = p->plane.x;
	p->plane.x = p->plane.x * c - p->plane.y * s;
	p->plane.y = old * s + p->plane.y * c;
}

/* Somme des directions demandees ; droite = dir tourne de +90 : (-dy, dx) */
static t_vec	input_dir(t_game *g)
{
	t_vec	mv;

	mv.x = (g->keys[K_W] - g->keys[K_S]) * g->pl.dir.x
		+ (g->keys[K_D] - g->keys[K_A]) * -g->pl.dir.y;
	mv.y = (g->keys[K_W] - g->keys[K_S]) * g->pl.dir.y
		+ (g->keys[K_D] - g->keys[K_A]) * g->pl.dir.x;
	return (mv);
}

/* Rotation puis deplacement normalise : W+D pas plus rapide que W */
void	update_player(t_game *g, double dt)
{
	t_vec	mv;
	double	rot;
	double	len;

	rot = (g->keys[K_RIGHT] - g->keys[K_LEFT]) * ROT_SPEED * dt;
	if (rot != 0)
		rotate_player(&g->pl, rot);
	mv = input_dir(g);
	len = sqrt(mv.x * mv.x + mv.y * mv.y);
	if (len > 1e-9)
		try_move(g, mv.x / len * MOVE_SPEED * dt,
			mv.y / len * MOVE_SPEED * dt);
}
