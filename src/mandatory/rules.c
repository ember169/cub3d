#include "cub3d.h"

/*
** Points de variation mandatory (le bonus fournit rules_bonus.c, memes
** prototypes : map_check.c n'est jamais modifie).
**
** int is_map_char(char c)    renvoyer c est '0' '1' 'N' 'S' 'E' 'W' ou ' '
** int is_walkable(char c)    renvoyer c est '0' 'N' 'S' 'E' ou 'W'
** int is_solid(t_game *g, int x, int y)
**     renvoyer grid[y][x] == '1' (hors grille = solide)
** t_img *select_texture(t_game *g, t_ray *r)
**     selon la face touchee (hit_side) et le signe de r->dir :
**     renvoyer &g->tex[EL_NO | EL_SO | EL_WE | EL_EA]
*/
