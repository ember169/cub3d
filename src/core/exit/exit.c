# include "../../includes/cub3d.h"

/**
 * Règles du contrat
 * - [ ] `t_game g` est mis à zéro (`ft_bzero(&g, sizeof(g))`) au début de `main` : tous les pointeurs valent `NULL`, donc `exit_game` est appelable **depuis n'importe où**, même avant `mlx_init`.
 * - [ ] Tout ce qui est alloué et survit à une fonction est **rattaché à `g`** (propriétaire unique). Après chaque `free`, le pointeur repasse à `NULL`.
 * - [ ] Les fonctions « feuilles » (`parse_rgb`, `check_map`, `read_lines`…) **ne quittent jamais** : elles renvoient un code (un `int`, ou pour le parsing un message `E_*` / `NULL`, §8.1). Seules les fonctions « chef d'orchestre » (`parse_scene`, `gfx_init`, `main`, hooks) appellent `exit_game`, après avoir libéré leurs temporaires.
 * - [ ] Carte : `grid[y][x]`, `x` = colonne vers l'Est, `y` = ligne vers le Sud (même sens que l'écran).
 * - [ ] Couleur : `int` au format `0x00RRGGBB`.
 * - [ ] `zbuf`, `ext`, `ext_free` restent `NULL` en mandatory : ce sont les seuls crochets pour les bonus.
**/

