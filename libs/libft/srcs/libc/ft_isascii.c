/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:42:52 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_isascii                                                      */
/*                                                                            */
/*  Controle si la valeur donnee appartient au jeu ASCII standard.            */
/*                                                                            */
/*  @param c  Valeur numerique a tester.                                      */
/*  @return  1 si compris entre 0 et 127, sinon 0.                            */
/*                                                                            */
/*  if (!ft_isascii(200)) { ... }                                             */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
