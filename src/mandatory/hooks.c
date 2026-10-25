/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_close(t_game *g)
{
	exit_game(g, 0, NULL);
	return (0);
}

/* Pas de mlx_key_hook : sous Linux il se declenche au relachement */
void	setup_hooks(t_game *g)
{
	mlx_hook(g->win, KeyPress, KeyPressMask, on_key_press, g);
	mlx_hook(g->win, KeyRelease, KeyReleaseMask, on_key_release, g);
	mlx_hook(g->win, FocusOut, FocusChangeMask, on_focus_out, g);
	mlx_hook(g->win, DestroyNotify, 0, on_close, g);
	mlx_loop_hook(g->mlx, game_loop, g);
}
