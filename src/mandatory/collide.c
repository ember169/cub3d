/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 14:19:53 by lgervet           #+#    #+#             */
/*   Updated: 2026/10/31 10:32:17 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Collision du point, axe par axe : on glisse le long des murs */
void	try_move(t_game *g, double dx, double dy)
{
	if (!is_solid(g, (int)(g->pl.pos.x + dx), (int)g->pl.pos.y))
		g->pl.pos.x += dx;
	if (!is_solid(g, (int)g->pl.pos.x, (int)(g->pl.pos.y + dy)))
		g->pl.pos.y += dy;
}
