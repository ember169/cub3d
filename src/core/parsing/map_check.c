#include "cub3d.h"

/*
** P6 - Caracteres + joueur
** is_map_char vient de rules.c (point de variation : le bonus ajoute D et X).
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
** P7 - Fermeture de la map (sans recursion, sans flood fill)
**
** Regle : toute case marchable a ses 4 voisines (haut, bas, gauche, droite)
** dans la grille ET differentes de ' '. Bord de grille et espace = du vide.
** Les diagonales n'ont pas besoin d'etre testees (il faudrait traverser
** un des deux murs adjacents).
*/

/* Bornes testees AVANT la lecture de la case : || est paresseux */
static int	is_void(t_map *map, int y, int x)
{
	return (y < 0 || x < 0 || y >= map->h || x >= map->w
		|| map->grid[y][x] == ' ');
}

static int	touches_void(t_map *map, int y, int x)
{
	return (is_void(map, y - 1, x) || is_void(map, y + 1, x)
		|| is_void(map, y, x - 1) || is_void(map, y, x + 1));
}

/* 0 = fermee ; 1 = ouverte, (err_row, err_col) = 1re case fautive (debug) */
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
