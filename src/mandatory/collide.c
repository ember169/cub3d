/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by achavier         ###   ########.fr       */
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
