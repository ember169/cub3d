#include "cub3d.h"

/*
** P5 - Extraction de la map en grille rectangulaire h x w
**
** char *build_map(t_game *g, char **lines)
**   lines = premiere ligne apres le 6e element
**     i = 0 ; tant que lines[i] et is_blank(lines[i]) : i++
**     si !lines[i] -> E_NOMAP
**     h = nombre de lignes non blanches consecutives a partir de i
**     j = i + h
**     tant que lines[j] : si !is_blank(lines[j]) -> E_MAPGAP ; j++
**         (lignes vides FINALES acceptees, contenu apres la map refuse)
**     w = longueur max des lignes i .. i + h - 1
**     g->map.grid = ft_calloc(h + 1, sizeof(char *))     NULL -> E_MALLOC
**         (rattachee a g AVANT de remplir : exit_game libere le partiel)
**     pour y de 0 a h - 1 :
**         grid[y] = malloc(w + 1)                        NULL -> E_MALLOC
**         remplir de ' ' sur w caracteres
**         copier lines[i + y] au debut
**         grid[y][w] = '\0'
**     g->map.w = w ; g->map.h = h
**     renvoyer NULL
**
** Pourquoi completer par des espaces : grid[y][x] devient lisible pour tout
** 0 <= x < w, 0 <= y < h ; "au-dela de la ligne" = du vide = un espace.
*/
