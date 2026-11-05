/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 11:23:47 by lgervet           #+#    #+#             */
/*   Updated: 2026/10/29 15:41:55 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Initialisation du cone de vision:
**	- dir: sens du regard
**	- plane: perpendiculaire a dir, represente la width de la fenetre
**	- FOV: determine l'angle du cone de vision. 0.66 car c'est a peu pres le 
**	champs humain: (FOV = 2 * atan(plane / dir) = 2 * atan(0.66) ≈ 66.8°)
*/
static void	set_dir(t_player *p, char c)
{
	p->dir.x = 0;
	p->dir.y = 0;
	if (c == 'N')
		p->dir.y = -1;
	else if (c == 'S')
		p->dir.y = 1;
	else if (c == 'E')
		p->dir.x = 1;
	else
		p->dir.x = -1;
	p->plane.x = -p->dir.y * FOV_PLANE;
	p->plane.y = p->dir.x * FOV_PLANE;
}

/* 
** - Identifie la position du joueur (+0.5 pour centrer sur la case)
** - Initialise la direction du regard. 
** - La case devient 0 (walkable) pour le rendu
*/
void	init_player(t_game *g)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < g->map.h)
	{
		x = 0;
		while (x < g->map.w)
		{
			c = g->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				g->pl.pos.x = x + 0.5;
				g->pl.pos.y = y + 0.5;
				set_dir(&g->pl, c);
				g->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
