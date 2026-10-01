/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:44:16 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_putstr_fd                                                    */
/*                                                                            */
/*  Outputs the string ’s’ to the specified file descriptor.                  */
/*                                                                            */
/*  @param s  The string to output                                            */
/*  @param fd  The file descriptor on which to write                          */
/*  @return       None                                                        */
/*                                                                            */
/*  Example:                                                                  */
/*     ft_putstr_fd(s, fd);                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
