/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:52:05 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_putendl_fd                                                   */
/*                                                                            */
/*  Outputs the string ’s’ to the specified file descriptor followed          */
/*	by a newline                                                              */
/*                                                                            */
/*  @param s  The string to output                                            */
/*  @param fd  The file descriptor on which to write                          */
/*  @return       None                                                        */
/*                                                                            */
/*  Example:                                                                  */
/*     int *arr = ft_calloc(10, sizeof(int));                                 */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
