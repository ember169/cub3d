/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:43:22 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_memchr                                                       */
/*                                                                            */
/*  Recherche la premiere occurrence d'un octet donne dans une zone.          */
/*                                                                            */
/*  @param s  Adresse du bloc de memoire source.                              */
/*  @param c  Octet recherche.                                                */
/*  @param n  Nombre d'octets a inspecter.                                    */
/*  @return  Pointeur sur l'octet trouve ou NULL.                             */
/*                                                                            */
/*  unsigned char *hit = ft_memchr(buffer, '\n', len);                        */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	return (NULL);
}
