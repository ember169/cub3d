#include "cub3d.h"

/* Usage : ./t_file fichier.cub -> affiche [ligne] pour chaque ligne lue */
int	main(int argc, char **argv)
{
	char	**lines;
	int		err;
	int		i;

	if (argc != 2)
		return (1);
	err = 0;
	lines = read_lines(argv[1], &err);
	ft_printf("err=%d ext=%d readable=%d\n", err,
		check_extension(argv[1], ".cub"), check_readable_file(argv[1]));
	i = 0;
	while (lines && lines[i])
		ft_printf("[%s]\n", lines[i++]);
	free_tab(lines);
	return (0);
}
