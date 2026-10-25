/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Hors grille et espace comptent comme des murs : le DDA s'arrete toujours */
int	is_solid(t_game *g, int x, int y)
{
	if (x < 0 || y < 0 || x >= g->map.w || y >= g->map.h)
		return (1);
	return (g->map.grid[y][x] == '1' || g->map.grid[y][x] == ' ');
}

/* Convention 7.8 : NO = texture vue en regardant vers le Nord (y < 0) */
t_img	*select_texture(t_game *g, t_ray *r)
{
	if (r->hit_side == 1)
	{
		if (r->dir.y < 0)
			return (&g->tex[EL_NO]);
		return (&g->tex[EL_SO]);
	}
	if (r->dir.x > 0)
		return (&g->tex[EL_EA]);
	return (&g->tex[EL_WE]);
}
