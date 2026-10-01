/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:30:04 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_split                                                        */
/*                                                                            */
/*  Allocates memory (using malloc(3)) and returns an array of strings        */
/*  obtained by splitting ’s’ using the character ’c’ as a delimiter.         */
/*  The array must end with a NULL pointer                                    */
/*                                                                            */
/*  @param s  The string to be split.                                         */
/*  @param c  The delimiter character.                                        */
/*  @return   The array of new strings / NULL if the allocation fails.        */
/*                                                                            */
/*  Example:                                                                  */
/*     int *arr = ft_calloc(10, sizeof(int));                                 */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t	_countwords(char const *s, char c)
{
	int	n;
	int	i;

	n = 1;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			n++;
		i++;
	}
	return (n);
}

static void	_freearr(char **arr, size_t n)
{
	while (n--)
		free(arr[n]);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	start;
	size_t	i;
	size_t	j;
	char	**arr;

	arr = (char **)malloc((_countwords(s, c) + 1) * sizeof(*arr));
	if (!arr || !s)
		return (_freearr(arr, 0), NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start == i)
			continue ;
		arr[j] = ft_substr(s, start, i - start);
		if (!arr[j])
			return (_freearr(arr, j), NULL);
		j++;
	}
	return (arr[j] = NULL, arr);
}
