#include "cub3d.h"

/*
** Points de variation mandatory (le bonus fournit rules_bonus.c, memes
** prototypes : map_check.c n'est jamais modifie).
*/

/* c != '\0' : ft_strchr trouverait le terminateur de la chaine */
int	is_map_char(char c)
{
	return (c != '\0' && ft_strchr("01NSEW ", c) != NULL);
}

int	is_walkable(char c)
{
	return (c != '\0' && ft_strchr("0NSEW", c) != NULL);
}

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
