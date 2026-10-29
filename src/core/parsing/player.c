/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 11:17:08 by lgervet           #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** P8 - Initialisation du joueur (ne peut pas echouer : P6 a garanti 1 joueur)
**
** Repere : x vers l'Est, y vers le SUD (donc Nord = y negatif).
** plane = dir tourne de 90 degres vers la droite, mis a l'echelle du FOV :
**   N dir (0,-1) plane (0.66,0)    S dir (0,1)  plane (-0.66,0)
**   E dir (1,0)  plane (0,0.66)    W dir (-1,0) plane (0,-0.66)
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

/* pos = centre de la case ; la lettre devient '0' (case vide pour le rendu) */
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
