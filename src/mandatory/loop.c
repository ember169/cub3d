/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Redessine a chaque tour : l'image revient seule apres minimisation.
** dt plafonne : une frame tres lente (valgrind) ne traverse pas un mur */
int	game_loop(t_game *g)
{
	double	t;
	double	dt;

	t = now_seconds();
	dt = t - g->last_time;
	g->last_time = t;
	if (dt > MAX_DT)
		dt = MAX_DT;
	update_player(g, dt);
	render_frame(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.ptr, 0, 0);
	return (0);
}
