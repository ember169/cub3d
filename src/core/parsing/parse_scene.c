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
}
