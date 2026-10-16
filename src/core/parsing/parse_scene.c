#include "cub3d.h"

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
	if (!g->sc.lines)
		exit_game(g, 1, E_EMPTY);

	/*
	** P2 - zone elements
	**     i = 0
	**     tant que lines[i] ET found != ALL_ELEMS :
	**         si !is_blank(lines[i]) : msg = parse_element(g, lines[i])
	**                                  si msg -> exit_game(g, 1, msg)
	**         i++
	**     si found != ALL_ELEMS -> exit_game(g, 1, E_MISSING)
	**
	** P5 - msg = build_map(g, lines + i)            si msg -> exit_game
	** P6 - msg = check_chars(&g->map)               si msg -> exit_game
	** P7 - si check_map(&g->map, &row, &col)        -> exit_game(E_OPENMAP)
	** P8 - init_player(g)
	**
	** Fin : free_tab(g->sc.lines) ; g->sc.lines = NULL
	*/
}
