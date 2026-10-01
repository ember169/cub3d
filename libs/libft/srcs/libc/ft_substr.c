/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:14:20 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_substr                                                       */
/*                                                                            */
/*  Allocates memory (using malloc(3)) and returns a substring from the       */
/*	string ’s’. The substring starts at index ’start’ and has a maximum       */
/*	length of ’len’.                                                          */
/*                                                                            */
/*                                                                            */
/*  @param s      The original string from which to create the substring.     */
/*  @param start  The starting index of the substring within 's'.             */
/*	@param len    The maximum length of the substring.                        */
/*  @return       The substring / NULL if the allocation fails.               */
/*                                                                            */
/*  Example:                                                                  */
/*     printf("%s", ft_substr("Lorem ipsum dolor sit amet", start, len));     */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	n;
	char	*s2;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if ((size_t)start >= slen)
		return (ft_strdup(""));
	if (len < (slen - (size_t)start))
		n = len;
	else
		n = slen - (size_t)start;
	s2 = (char *)malloc(n + 1);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s + start, n + 1);
	return (s2);
}
