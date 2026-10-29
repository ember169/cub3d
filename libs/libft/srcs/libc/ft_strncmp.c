/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:45:10 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_strncmp                                                      */
/*                                                                            */
/*  Compare deux chaines jusqu'a n caracteres maximum.                        */
/*                                                                            */
/*  @param s1  Premiere chaine.                                               */
/*  @param s2  Seconde chaine.                                                */
/*  @param n   Nombre maximum de caracteres a comparer.                       */
/*  @return  Difference entre les premiers caracteres distincts ou 0.         */
/*                                                                            */
/*  int cmp = ft_strncmp("abc", "abd", 3);                                    */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
