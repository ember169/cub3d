/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:42:12 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_bzero                                                        */
/*                                                                            */
/*  Met a zero chaque octet d'une zone memoire donnee.                        */
/*                                                                            */
/*  @param s  Adresse du bloc de memoire a nettoyer.                          */
/*  @param n  Nombre d'octets a initialiser a zero.                           */
/*  @return  Rien.                                                            */
/*                                                                            */
/*  ft_bzero(buffer, 32);                                                     */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *) s;
	while (n--)
		*str++ = 0;
	return ;
}
