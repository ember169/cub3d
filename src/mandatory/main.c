#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	g;

	ft_bzero(&g, sizeof(g));
	if (argc != 2)
		exit_game(&g, 1, E_USAGE);
	parse_scene(&g, argv[1]);
	exit_game(&g, 0, NULL);
	return (0);
}
