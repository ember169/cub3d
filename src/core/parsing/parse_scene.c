#include "cub3d.h"

static int	all_blank(char **lines)
{
	int	i;

	i = 0;
	while (lines && lines[i])
	{
		if (!is_blank(lines[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** P2 - Zone elements. S'arrete DES que les 6 sont vus : la ligne non blanche
** suivante est forcement la map. Renvoie l'indice de la ligne qui suit le
** 6e element.
*/
static int	parse_elements(t_game *g)
{
	int		i;
	char	*msg;

	i = 0;
	while (g->sc.lines[i] && g->sc.found != ALL_ELEMS)
	{
		if (!is_blank(g->sc.lines[i]))
		{
			msg = parse_element(g, g->sc.lines[i]);
			if (msg)
				exit_game(g, 1, msg);
		}
		i++;
	}
	if (g->sc.found != ALL_ELEMS)
		exit_game(g, 1, E_MISSING);
	return (i);
}

/* P5 -> P8 : chaque etape ne tourne que si la precedente a reussi */
static void	parse_map(t_game *g, int i)
{
	char	*msg;
	int		row;
	int		col;

	msg = build_map(g, g->sc.lines + i);
	if (!msg)
		msg = check_chars(&g->map);
	if (!msg && check_map(&g->map, &row, &col))
		msg = E_OPENMAP;
	if (msg)
		exit_game(g, 1, msg);
	init_player(g);
}

void	parse_scene(t_game *g, char *path)
{
	int	err;

	if (!check_extension(path, ".cub"))
		exit_game(g, 1, E_EXT);
	err = check_readable_file(path);
	if (err == 1)
		exit_game(g, 1, E_ISDIR);
	if (err == 2)
		exit_game(g, 1, E_OPEN);
	err = 0;
	g->sc.lines = read_lines(path, &err);
	if (err)
		exit_game(g, 1, E_MALLOC);
	if (all_blank(g->sc.lines))
		exit_game(g, 1, E_EMPTY);
	parse_map(g, parse_elements(g));
	free_tab(g->sc.lines);
	g->sc.lines = NULL;
}
