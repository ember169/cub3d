/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:44:18 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_strlcat                                                      */
/*                                                                            */
/*  Concatene src a dst sans depasser la taille disponible.                   */
/*                                                                            */
/*  @param dst      Buffer de destination.                                    */
/*  @param src      Chaine a ajouter.                                         */
/*  @param dstsize  Taille totale du buffer.                                  */
/*  @return  Longueur attendue (dst initial + src).                           */
/*                                                                            */
/*  size_t len = ft_strlcat(buffer, suffix, sizeof(buffer));                  */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	j;
	size_t	src_len;

	dst_len = 0;
	while (dst_len < dstsize && dst[dst_len])
		dst_len++;
	j = 0;
	while (src[j])
		j++;
	src_len = j;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	j = 0;
	while (src[j] && dst_len < dstsize - 1)
	{
		dst[dst_len] = src[j];
		dst_len++;
		j++;
	}
	dst[dst_len] = '\0';
	return (dst_len + (src_len - j));
}
