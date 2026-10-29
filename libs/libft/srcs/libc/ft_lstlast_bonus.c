/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:22:44 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_lstlast                                                      */
/*                                                                            */
/*  Returns the last node of the list                                         */
/*                                                                            */
/*  @param lst    The beginning of the list                                   */
/*  @return       Last node of the list                                       */
/*                                                                            */
/*  Example:                                                                  */
/*     int *arr = ft_calloc(10, sizeof(int));                                 */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*currentlst;

	if (!lst)
		return (NULL);
	currentlst = lst;
	while (currentlst->next)
		currentlst = currentlst->next;
	return (currentlst);
}
