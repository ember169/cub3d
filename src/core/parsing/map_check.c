/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:45:03 by lgervet           #+#    #+#             */
/*   Updated: 2026/10/30 14:22:08 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Parcours la map pour verifier le nombre de joueur (!= 1 = error)
*/
char	*check_chars(t_map *map)
{
	int		x;
	int		y;
	int		players;
	char	c;

	players = 0;
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			c = map->grid[y][x];
			if (!is_map_char(c))
				return (E_MAPCHAR);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				players++;
			x++;
		}
		y++;
	}
	if (players != 1)
		return (E_PLAYER);
	return (NULL);
}

/*
** Regle : toute case marchable a ses 4 voisines (haut, bas, gauche, droite)
** dans la grille ET differentes de ' '. Les diagonales n'ont pas besoin 
** d'etre testees (il faudrait traverser un des deux murs adjacents).
*/

/* 
** Verifie si une case est vide ou hors-map
*/
static int	is_void(t_map *map, int y, int x)
{
	return (y < 0 || x < 0 || y >= map->h || x >= map->w
		|| map->grid[y][x] == ' ');
}

/* 
** Verifie si les cases voisines sont vides ou hors-map
*/
static int	touches_void(t_map *map, int y, int x)
{
	return (is_void(map, y - 1, x) || is_void(map, y + 1, x)
		|| is_void(map, y, x - 1) || is_void(map, y, x + 1));
}

/* 
** Verifie que la map est entouree de murs.
** Si une case a un voisin void note les coordonnees pour debug
** Retourne 0 = fermee ; 1 = ouverte
*/
int	check_map(t_map *map, int *err_row, int *err_col)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (is_walkable(map->grid[y][x]) && touches_void(map, y, x))
			{
				*err_row = y;
				*err_col = x;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
