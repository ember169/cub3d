/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:01:15 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_strmapi                                                      */
/*                                                                            */
/*  Applies the function f to each character of the string s, passing its     */
/*	index as the first argument and the character itself as the second. A new */
/*	string is created (using malloc(3)) to store the results from the         */
/*	successive applications of f                                              */
/*                                                                            */
/*  @param s  The string to iterate over                                      */
/*  @param f  The function to apply to each character                         */
/*  @return   The string created / NULL if allocation failed                  */
/*                                                                            */
/*  Example:                                                                  */
/*     int *str = ft_strmapi(s, change_char(s, 32)));                         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
