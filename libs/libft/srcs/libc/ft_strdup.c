/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:44:01 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_strdup                                                       */
/*                                                                            */
/*  Alloue suffisamment de memoire et retourne un pointeur vers une copie     */
/*  d'une chaine de caractere												  */
/*                                                                            */
/*  @param s1  Chaine de caractere a dupliquer                                */
/*  @return    Pointeur vers la nouvelle chaine ou NULL si trop peu de memory */
/*                                                                            */
/*  Example:                                                                  */
/*     char *str2 = ft_strdup(str1);                                          */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	l;
	size_t	i;
	char	*s2;

	l = ft_strlen(s1);
	s2 = (char *)malloc((l + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
