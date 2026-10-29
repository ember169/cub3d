/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:07:51 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_lstsize                                                      */
/*                                                                            */
/*  Counts the number of nodes in the list.                                   */
/*                                                                            */
/*  @param lst  The beginning of the list                                     */
/*  @return       The length of the list                                      */
/*                                                                            */
/*  Example:                                                                  */
/*     int i = ft_lstsize(l1);                                                */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*currentlist;

	if (!lst)
		return (0);
	i = 1;
	currentlist = lst;
	while (currentlist->next)
	{
		currentlist = currentlist->next;
		i++;
	}
	return (i);
}
