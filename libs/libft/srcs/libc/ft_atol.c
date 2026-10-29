/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:23:01 by lgervet           #+#    #+#             */
/*   Updated: 2026/01/25 15:28:08 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_atol                                                         */
/*                                                                            */
/*  Convertit une chaine representant un nombre en entier long signe.         */
/*                                                                            */
/*  @param str  Chaine a analyser.                                            */
/*  @return  Entier long signe converti.                                      */
/*                                                                            */
/*  int value = ft_atol("  -42");                                             */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

long	ft_atol(const char *str)
{
	long	i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
