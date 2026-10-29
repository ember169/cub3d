/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 11:17:08 by lgervet           #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** P4 - Couleurs : " 220, 100 ,0" -> 0x00DC6400. Aucune allocation.
**
** Automate lu une seule fois, de gauche a droite :
**   espaces* chiffres+ espaces* ',' espaces* chiffres+ espaces* ','
**   espaces* chiffres+ espaces* fin
**
** Pas de ft_atoi (accepte '+', '-', deborde) ni de ft_split (fusionne les ',').
*/

/* Lit "espaces nombre espaces" ; refuse > 255 PENDANT la lecture */
static int	read_component(char *s, int *i, int *val)
{
	int	nb;

	while (s[*i] == ' ')
		(*i)++;
	*val = 0;
	nb = 0;
	while (ft_isdigit(s[*i]))
	{
		*val = *val * 10 + (s[*i] - '0');
		nb++;
		(*i)++;
		if (*val > 255)
			return (1);
	}
	if (nb == 0)
		return (1);
	while (s[*i] == ' ')
		(*i)++;
	return (0);
}

/* 0 = OK (*out = 0x00RRGGBB), 1 = erreur */
int	parse_rgb(char *s, int *out)
{
	int	i;
	int	k;
	int	val;
	int	rgb;

	i = 0;
	k = 0;
	rgb = 0;
	while (k < 3)
	{
		if (read_component(s, &i, &val))
			return (1);
		rgb = (rgb << 8) | val;
		if (k < 2 && s[i] != ',')
			return (1);
		if (k < 2)
			i++;
		k++;
	}
	if (s[i] != '\0')
		return (1);
	*out = rgb;
	return (0);
}
