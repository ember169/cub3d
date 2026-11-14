/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:52:09 by lgervet           #+#    #+#             */
/*   Updated: 2026/11/13 15:14:48 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Valide et store les chemins des textures
** !tok[0] || tok[1] = il n'y a pas EXACTEMENT un seul token (0 ou > 1).
*/
char	*parse_texture(t_game *g, int el, char *rest)
{
	char	**tok;
	char	*msg;

	tok = ft_split(rest, ' ');
	if (!tok)
		return (E_MALLOC);
	msg = NULL;
	if (!tok[0] || tok[1])
		msg = E_TEXPATH;
	else if (!check_extension(tok[0], ".xpm"))
		msg = E_TEXPATH;
	else if (check_readable_file(tok[0]) != 0)
		msg = E_TEXPATH;
	else
	{
		g->sc.tex_path[el] = ft_strdup(tok[0]);
		if (!g->sc.tex_path[el])
			msg = E_MALLOC;
	}
	free_tab(tok);
	return (msg);
}
