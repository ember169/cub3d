#include "cub3d.h"

/*
** Usage : ./t_parse fichier.cub -> parse_scene puis debug_dump
** Build (depuis la racine, apres make) : compiler ce fichier + debug_dump.c
** + tous les .o de cub3D SAUF src/mandatory/main.o, avec les memes -I et
** le meme LDFLAGS que le Makefile, -o t_parse.
*/
void	debug_dump(t_game *g);

int	main(int argc, char **argv)
{
	t_game	g;

	ft_bzero(&g, sizeof(g));
	if (argc != 2)
		exit_game(&g, 1, E_USAGE);
	parse_scene(&g, argv[1]);
	debug_dump(&g);
	exit_game(&g, 0, NULL);
	return (0);
}
