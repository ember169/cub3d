/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:45:23 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_strrchr                                                      */
/*                                                                            */
/*  Cherche la derniere occurrence d'un caractere dans une chaine.            */
/*                                                                            */
/*  @param s  Chaine source.                                                  */
/*  @param c  Caractere cible.                                                */
/*  @return  Adresse de la derniere occurrence ou NULL.                       */
/*                                                                            */
/*  char *ext = ft_strrchr(filename, '.');                                    */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_char;

	last_char = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last_char = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (last_char);
}
