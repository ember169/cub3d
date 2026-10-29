/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:46:12 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_toupper                                                      */
/*                                                                            */
/*  Convertit une lettre minuscule ASCII en majuscule.                        */
/*                                                                            */
/*  @param c  Caractere a transformer.                                        */
/*  @return  Caractere converti ou identique s'il n'est pas minuscule.        */
/*                                                                            */
/*  char upper = ft_toupper('z');                                             */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
