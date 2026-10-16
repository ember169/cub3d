#include "cub3d.h"

/*
** P8 - Initialisation du joueur (ne peut pas echouer : P6 a garanti 1 joueur)
**
** void init_player(t_game *g)
**     trouver (x, y) tel que grid[y][x] est N, S, E ou W
**     pos   = (x + 0.5, y + 0.5)                  centre de la case
**     dir   = N (0, -1) | S (0, 1) | E (1, 0) | W (-1, 0)
**     plane = (-dir.y * FOV_PLANE, dir.x * FOV_PLANE)
**     grid[y][x] = '0'      (le rendu ne voit plus qu'une case vide)
**
** Pieges : oublier + 0.5 ; inverser x et y ; mauvais signe sur plane
** (monde en miroir).
*/
