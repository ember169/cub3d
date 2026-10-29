/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:43:02 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_isdigit                                                      */
/*                                                                            */
/*  Determine si un caractere represente un chiffre decimal.                  */
/*                                                                            */
/*  @param c  Code du caractere a verifier.                                   */
/*  @return  1 pour les caracteres '0'..'9', sinon 0.                         */
/*                                                                            */
/*  if (ft_isdigit('3')) { ... }                                              */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
