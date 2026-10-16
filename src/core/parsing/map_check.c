#include "cub3d.h"

/*
** P6 - Caracteres + joueur
**
** char *check_chars(t_map *map)
**     joueurs = 0
**     pour y de 0 a h - 1, pour x de 0 a w - 1 :
**         c = grid[y][x]
**         si !is_map_char(c)          -> E_MAPCHAR
**         si c est N, S, E ou W       -> joueurs++
**             (attention : ft_strchr("NSEW", '\0') est non nul)
**     si joueurs != 1 -> E_PLAYER
**     renvoyer NULL
*/

/*
** P7 - Fermeture de la map (sans recursion, sans flood fill)
**
** Regle : toute case marchable a ses 4 voisines (haut, bas, gauche, droite)
** dans la grille ET differentes de ' '. Bord de grille et espace = du vide.
** Les diagonales n'ont pas besoin d'etre testees (il faudrait traverser
** un des deux murs adjacents).
**
** static int is_void(t_map *map, int y, int x)
**     renvoyer y < 0 || x < 0 || y >= h || x >= w || grid[y][x] == ' '
**     (bornes testees AVANT la lecture : || paresseux)
**
** int check_map(t_map *map, int *err_row, int *err_col)
**     pour y de 0 a h - 1, pour x de 0 a w - 1 :
**         si is_walkable(grid[y][x]) ET
**            (is_void(y-1, x) OU is_void(y+1, x)
**             OU is_void(y, x-1) OU is_void(y, x+1)) :
**             *err_row = y ; *err_col = x ; renvoyer 1
**     renvoyer 0
**
** Le joueur (N S E W) est marchable : i_player_on_edge doit echouer.
*/
