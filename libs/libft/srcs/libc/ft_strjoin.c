/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:50:14 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_strjoin                                                      */
/*                                                                            */
/*  Allocates memory (using malloc(3)) and returns a new string, which is     */
/*  the result of concatenating ’s1’ and ’s2’.                                */
/*                                                                            */
/*  @param s1      Prefix string.                                             */
/*  @param s2      Suffix string.                                             */
/*  @return        The new string / NULL if the allocation fails.             */
/*                                                                            */
/*  Example:                                                                  */
/*     printf("%s\n", ft_strjoin("Lorem", " ipsum"));                         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l;
	char	*s3;
	size_t	i;
	size_t	j;

	l = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc((l + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}
