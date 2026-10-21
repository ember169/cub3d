#include "cub3d.h"

/*
** Usage : ./t_elements (depuis la racine, apres bash tests/gen_maps.sh)
** Appelle parse_element / parse_rgb sur des chaines en dur et affiche le
** resultat : comparer avec la colonne "attendu".
** Build : comme t_parse.c, en remplacant t_parse.c et debug_dump.c par
** ce fichier.
*/
static void	elem(char *line, char *expected)
{
	t_game	g;
	char	*msg;

	ft_bzero(&g, sizeof(g));
	msg = parse_element(&g, line);
	if (!msg)
		msg = "OK";
	ft_printf("[%s] -> %s (attendu: %s)\n", line, msg, expected);
	free_scene(&g.sc);
}

static void	rgb(char *s, char *expected)
{
	int	out;

	out = -1;
	if (parse_rgb(s, &out))
		ft_printf("rgb \"%s\" -> erreur  attendu: %s\n", s, expected);
	else
		ft_printf("rgb \"%s\" -> 0x%X  attendu: %s\n", s, out, expected);
}

int	main(void)
{
	elem("NO ./textures/test/no.xpm", "OK");
	elem("  F 1,2,3  ", "OK");
	elem("NOPE x", E_IDENT);
	elem("NO./textures/test/no.xpm", E_IDENT);
	elem("no ./textures/test/no.xpm", E_IDENT);
	elem("F", E_COLOR);
	elem("NO", E_TEXPATH);
	elem("111111", E_MISSING);
	elem("NO\t./textures/test/no.xpm", E_BADSPACE);
	rgb("255,255,255", "0xFFFFFF");
	rgb("0,0,0", "0x0");
	rgb(" 220 , 100 ,0 ", "0xDC6400");
	rgb("220,100,0,", "erreur");
	rgb("256,0,0", "erreur");
	rgb("+1,0,0", "erreur");
	return (0);
}
