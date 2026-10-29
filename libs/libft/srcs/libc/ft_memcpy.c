/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:43:37 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_memcpy                                                       */
/*                                                                            */
/*  Copie un bloc memoire vers une autre adresse sans gerer les recouvrements.*/
/*                                                                            */
/*  @param dst  Destination de la copie.                                      */
/*  @param src  Source a copier.                                              */
/*  @param n    Nombre d'octets a transferer.                                 */
/*  @return  Pointeur vers dst ou NULL si invalide.                           */
/*                                                                            */
/*  ft_memcpy(dest, src, len);                                                */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	while (n--)
		*d++ = *s++;
	return (dst);
}
