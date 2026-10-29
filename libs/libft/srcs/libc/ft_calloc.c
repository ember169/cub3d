/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:18:59 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_calloc                                                       */
/*                                                                            */
/*  Alloue un tableau en memoire et initialise chaque octet a zero.           */
/*                                                                            */
/*  @param nmemb  Nombre d'elements a reserver.                               */
/*  @param size   Taille en octets d'un element.                              */
/*  @return       Pointeur sur la zone zeroee ou NULL en cas d'erreur.        */
/*                                                                            */
/*  int *arr = ft_calloc(10, sizeof(int));                                    */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*buffer;

	if (nmemb != 0 && size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	buffer = malloc(total_size);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, total_size);
	return (buffer);
}
