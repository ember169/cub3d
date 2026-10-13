/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achavier <achavier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by achavier          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by achavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* line_len (octets par ligne) peut depasser w * 4 : ne jamais le recalculer */
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/* Clamp : tex_x peut valoir w quand wall_x arrondit a 1.0 */
int	get_texel(t_img *tex, int x, int y)
{
	char	*src;

	if (x < 0)
		x = 0;
	if (x >= tex->w)
		x = tex->w - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->h)
		y = tex->h - 1;
	src = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)src);
}
