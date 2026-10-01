/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:13:35 by lgervet           #+#    #+#             */
/*   Updated: 2026/02/05 12:59:28 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

/*
** ft_realloc:
**     Créé un malloc, free l'ancien et remplace par le nouveau
**
**     @param ptr  		pointeur vers le malloc a reallouer
**     @param old_size  la taille actuelle du malloc
**     @param new_size  la nouvelle taille du malloc
**     @return 			le pointeur vers le nouveau malloc / NULL si erreur
*/
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	unsigned char	*new;
	unsigned char	*old;
	size_t			copy_size;
	size_t			i;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	new = malloc(new_size);
	if (!new)
		return (NULL);
	old = (unsigned char *)ptr;
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	i = 0;
	while (i < copy_size)
	{
		new[i] = old[i];
		i++;
	}
	free(ptr);
	return (new);
}
