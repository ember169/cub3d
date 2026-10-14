#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_scene(t_scene *sc)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(sc->tex_path[i]);
		sc->tex_path[i] = NULL;
		i++;
	}
	free_tab(sc->lines);
	sc->lines = NULL;
}
