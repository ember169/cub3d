#include "cub3d.h"

/*
** P5 - Extraction de la map en grille rectangulaire h x w
**
** Pourquoi completer par des espaces : grid[y][x] devient lisible pour tout
** 0 <= x < w, 0 <= y < h ; "au-dela de la ligne" = du vide = un espace.
*/

static int	map_width(char **lines, int h)
{
	int	w;
	int	y;
	int	len;

	w = 0;
	y = 0;
	while (y < h)
	{
		len = ft_strlen(lines[y]);
		if (len > w)
			w = len;
		y++;
	}
	return (w);
}

/* grid rattachee a g AVANT d'etre remplie : exit_game libere le partiel */
static char	*fill_grid(t_game *g, char **lines, int h, int w)
{
	int	y;

	g->map.grid = ft_calloc(h + 1, sizeof(char *));
	if (!g->map.grid)
		return (E_MALLOC);
	y = 0;
	while (y < h)
	{
		g->map.grid[y] = malloc(w + 1);
		if (!g->map.grid[y])
			return (E_MALLOC);
		ft_memset(g->map.grid[y], ' ', w);
		ft_memcpy(g->map.grid[y], lines[y], ft_strlen(lines[y]));
		g->map.grid[y][w] = '\0';
		y++;
	}
	g->map.w = w;
	g->map.h = h;
	return (NULL);
}

/*
** lines = premiere ligne apres le 6e element.
** Lignes blanches avant la map : sautees. Apres la map : seules des lignes
** blanches sont tolerees (une ligne vide DANS la map coupe donc la map en
** deux, et la 2e moitie devient "du contenu apres la map" -> E_MAPGAP).
*/
char	*build_map(t_game *g, char **lines)
{
	int	i;
	int	h;
	int	j;

	i = 0;
	while (lines[i] && is_blank(lines[i]))
		i++;
	if (!lines[i])
		return (E_NOMAP);
	h = 0;
	while (lines[i + h] && !is_blank(lines[i + h]))
		h++;
	j = i + h;
	while (lines[j])
	{
		if (!is_blank(lines[j]))
			return (E_MAPGAP);
		j++;
	}
	return (fill_grid(g, lines + i, h, map_width(lines + i, h)));
}
