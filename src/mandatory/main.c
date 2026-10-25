/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* g a zero : exit_game est appelable de partout, meme avant mlx_init.
** last_time juste avant la boucle, sinon le premier dt est enorme */
int	main(int argc, char **argv)
{
	t_game	g;

	ft_bzero(&g, sizeof(g));
	if (argc != 2)
		exit_game(&g, 1, E_USAGE);
	parse_scene(&g, argv[1]);
	gfx_init(&g);
	setup_hooks(&g);
	g.last_time = now_seconds();
	mlx_loop(g.mlx);
	exit_game(&g, 0, NULL);
	return (0);
}
