/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:42:39 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_isalpha                                                      */
/*                                                                            */
/*  Indique si un caractere appartient a l'alphabet ASCII.                    */
/*                                                                            */
/*  @param c  Code du caractere a analyser.                                   */
/*  @return  1 pour une lettre, sinon 0.                                      */
/*                                                                            */
/*  if (ft_isalpha('z')) { ... }                                              */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}
