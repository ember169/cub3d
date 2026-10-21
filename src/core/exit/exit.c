#include "cub3d.h"

void	exit_game(t_game *g, int status, char *msg)
{
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	if (g->ext_free)
		g->ext_free(g);
	free_scene(&g->sc);
	free_tab(g->map.grid);
	g->map.grid = NULL;
	destroy_gfx(g);
	exit(status);
}

void	destroy_gfx(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->tex[i].ptr)
			mlx_destroy_image(g->mlx, g->tex[i].ptr);
		g->tex[i].ptr = NULL;
		i++;
	}
	if (g->frame.ptr)
		mlx_destroy_image(g->mlx, g->frame.ptr);
	g->frame.ptr = NULL;
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	g->win = NULL;
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	g->mlx = NULL;
}
