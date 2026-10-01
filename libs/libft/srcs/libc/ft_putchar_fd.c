/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:55:21 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_putchar_fd                                                   */
/*                                                                            */
/*  Outputs the character ’c’ to the specified file descriptor                */
/*                                                                            */
/*  @param c  The character to output                                         */
/*  @param fd  The file descriptor on which to write                          */
/*  @return       None                                                        */
/*                                                                            */
/*  Example:                                                                  */
/*     ft_putchar_fd(c, fd);                                                  */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
