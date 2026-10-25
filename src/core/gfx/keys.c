/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_index(int keysym)
{
	if (keysym == XK_w)
		return (K_W);
	if (keysym == XK_a)
		return (K_A);
	if (keysym == XK_s)
		return (K_S);
	if (keysym == XK_d)
		return (K_D);
	if (keysym == XK_Left)
		return (K_LEFT);
	if (keysym == XK_Right)
		return (K_RIGHT);
	return (-1);
}

/* On ne bouge pas ici : on note l'etat, game_loop fait le mouvement */
int	on_key_press(int keysym, t_game *g)
{
	int	i;

	if (keysym == XK_Escape)
		exit_game(g, 0, NULL);
	i = key_index(keysym);
	if (i >= 0)
		g->keys[i] = 1;
	return (0);
}

int	on_key_release(int keysym, t_game *g)
{
	int	i;

	i = key_index(keysym);
	if (i >= 0)
		g->keys[i] = 0;
	return (0);
}

/* Alt+Tab en tenant une touche : le KeyRelease part vers l'autre fenetre */
int	on_focus_out(t_game *g)
{
	int	i;

	i = 0;
	while (i < K_COUNT)
		g->keys[i++] = 0;
	return (0);
}
