/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:54:34 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_lstclear                                                     */
/*                                                                            */
/*  Deletes and frees the given node and all its successors, using the        */
/*  function ’del’ and free(3). Finally, set the pointer to the list to NULL  */
/*                                                                            */
/*  @param lst.    The address of a pointer to a node                         */
/*  @param del     The address of the function used to delete the content     */
/*				   of the node                                                */
/*  @return        None                                                       */
/*                                                                            */
/*  Example:                                                                  */
/*     int *arr = ft_calloc(10, sizeof(int));                                 */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lstnext;

	if (!lst || !(del))
		return ;
	while (*lst)
	{
		lstnext = (*lst)->next;
		(del)((*lst)->content);
		free(*lst);
		*lst = lstnext;
	}
	*lst = NULL;
}
