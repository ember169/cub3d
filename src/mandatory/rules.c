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

/*
** A FAIRE (M2 / R5) :
** int is_solid(t_game *g, int x, int y)
**     renvoyer grid[y][x] == '1' (hors grille = solide)
** t_img *select_texture(t_game *g, t_ray *r)
**     selon la face touchee (hit_side) et le signe de r->dir :
**     renvoyer &g->tex[EL_NO | EL_SO | EL_WE | EL_EA]
*/
