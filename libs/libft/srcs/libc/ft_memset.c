/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:44:00 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_memset                                                       */
/*                                                                            */
/*  Remplit une zone memoire avec l'octet fourni.                             */
/*                                                                            */
/*  @param b    Adresse du bloc a modifier.                                   */
/*  @param c    Valeur de l'octet a ecrire.                                   */
/*  @param len  Nombre d'octets a remplir.                                    */
/*  @return  Pointeur vers la zone modifiee.                                  */
/*                                                                            */
/*  ft_memset(buffer, 0xff, size);                                            */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	byte;

	p = (unsigned char *) b;
	byte = (unsigned char) c;
	while (len--)
		*p++ = byte;
	return (b);
}
