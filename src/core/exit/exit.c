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

void	exit_game(t_game *g, int status, char *msg);
{
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	if (g->ext_free)
		g->ext_free(g);
	free_tab(g->map.grid);
	g->map.grid = NULL;
	destroy_gfx(g);
	exit(status);
}

void	free_tab(char **tab)
{
	return ;
}

void	destroy_gfx(t_game *g);
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (g->tex[i].ptr)
			mlx_destroy_image(g->mlx, g->frame.ptr);
		if (g->frame.ptr)
			mlx_destroy_image(g->mlx, g->frame.ptr);
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
		if (g->mlx)
		{
			mlx_destroy_display(g->mlx);
			free(g->mlx);
		}
	}
}
