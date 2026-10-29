/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:43:47 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_memmove                                                      */
/*                                                                            */
/*  Copie n octets entre deux zones en gerant les recouvrements.              */
/*                                                                            */
/*  @param dst  Destination de la copie.                                      */
/*  @param src  Source a dupliquer.                                           */
/*  @param len  Longueur en octets a transferer.                              */
/*  @return  Pointeur vers dst ou NULL si les pointeurs sont invalides.       */
/*                                                                            */
/*  ft_memmove(buf + 1, buf, size);                                           */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!src && !dst)
		return (NULL);
	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	if (s > d)
	{
		while (len--)
			*d++ = *s++;
	}
	else if (d > s)
	{
		d += len;
		s += len;
		while (len--)
			*--d = *--s;
	}
	return (dst);
}
