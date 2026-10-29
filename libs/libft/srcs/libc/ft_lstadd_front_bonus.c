/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:22:05 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_lstadd_front                                                 */
/*                                                                            */
/*  Adds the node ’new’ at the beginning of the list                          */
/*                                                                            */
/*  @param lst  The address of a pointer to the first node of a list          */
/*  @param new  The address of a pointer to the node to be added              */
/*  @return       None                                                        */
/*                                                                            */
/*  Example:                                                                  */
/*     ft_lstadd_front(&l1, l2);                                              */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
