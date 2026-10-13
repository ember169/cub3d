/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* side = t du rayon au premier franchissement de ligne, dans chaque axe */
static void	init_step(t_ray *r, t_vec pos)
{
	if (r->dir.x < 0)
	{
		r->step_x = -1;
		r->side.x = (pos.x - r->map_x) * r->delta.x;
	}
	else
	{
		r->step_x = 1;
		r->side.x = (r->map_x + 1.0 - pos.x) * r->delta.x;
	}
	if (r->dir.y < 0)
	{
		r->step_y = -1;
		r->side.y = (pos.y - r->map_y) * r->delta.y;
	}
	else
	{
		r->step_y = 1;
		r->side.y = (r->map_y + 1.0 - pos.y) * r->delta.y;
	}
}

/* camera_x en double : 2 * x / WIN_W en int vaudrait toujours 0.
** A completer : run_dda (R2) puis perp (R3) */
void	cast_ray(t_game *g, int x, t_ray *r)
{
	double	camera_x;

	camera_x = 2.0 * x / WIN_W - 1.0;
	r->dir.x = g->pl.dir.x + g->pl.plane.x * camera_x;
	r->dir.y = g->pl.dir.y + g->pl.plane.y * camera_x;
	r->map_x = (int)g->pl.pos.x;
	r->map_y = (int)g->pl.pos.y;
	if (r->dir.x == 0)
		r->delta.x = 1e30;
	else
		r->delta.x = fabs(1 / r->dir.x);
	if (r->dir.y == 0)
		r->delta.y = 1e30;
	else
		r->delta.y = fabs(1 / r->dir.y);
	init_step(r, g->pl.pos);
}
