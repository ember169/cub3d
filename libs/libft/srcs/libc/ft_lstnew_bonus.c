/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:12:43 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_lstnew                                                       */
/*                                                                            */
/*  Allocates memory (using malloc(3)) and returns a new node. The ’content’  */
/*	member variable is initialized with the given parameter ’content’.        */
/*	The variable ’next’ is initialized to NULL                                */
/*                                                                            */
/*  @param content  The content to store in the new node.                     */
/*  @return      	A pointer to the new node.                                */
/*                                                                            */
/*  Example:                                                                  */
/*     int *arr = ft_calloc(10, sizeof(int));                                 */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l1;

	l1 = (t_list *)malloc(sizeof(t_list));
	if (!l1)
		return (NULL);
	l1->content = content;
	l1->next = NULL;
	return (l1);
}
