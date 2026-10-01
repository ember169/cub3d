/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:43:13 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_isprint                                                      */
/*                                                                            */
/*  Teste si le caractere appartient aux caracteres imprimables.              */
/*                                                                            */
/*  @param c  Valeur du caractere a tester.                                   */
/*  @return  1 pour les codes 32 a 126, sinon 0.                              */
/*                                                                            */
/*  if (ft_isprint('!')) { ... }                                              */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
