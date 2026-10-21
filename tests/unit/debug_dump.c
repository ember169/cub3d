#include <stdio.h>
#include "cub3d.h"

/*
** Affiche le resultat du parsing. Outil de test, hors Norme (printf pour
** les doubles). Les lignes de la grille sont entre [ ] pour voir les
** espaces de completement.
*/
void	debug_dump(t_game *g)
{
	static char	*names[4] = {"NO", "SO", "WE", "EA"};
	int			i;

	i = 0;
	while (i < 4)
	{
		printf("%s  %s\n", names[i], g->sc.tex_path[i]);
		i++;
	}
	printf("F   0x%06X\nC   0x%06X\n", g->sc.floor, g->sc.ceil);
	printf("map %d x %d (w x h)\n", g->map.w, g->map.h);
	i = 0;
	while (g->map.grid && g->map.grid[i])
		printf("[%s]\n", g->map.grid[i++]);
	printf("pos   (%.2f, %.2f)\n", g->pl.pos.x, g->pl.pos.y);
	printf("dir   (%.2f, %.2f)\n", g->pl.dir.x, g->pl.dir.y);
	printf("plane (%.2f, %.2f)\n", g->pl.plane.x + 0.0, g->pl.plane.y + 0.0);
}
