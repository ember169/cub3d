/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:30:51 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: ft_printf                                                       */
/*                                                                            */
/*  Formats and prints its arguments. Handles the following conversions: 	  */
/*	        																  */
/*	• %c Prints a single character.											  */
/*	• %s Prints a string (as defined by the common C convention).			  */
/*	• %p The void * pointer argument has to be printed in hexadecimal format. */
/*	• %d Prints a decimal (base 10) number.									  */
/*	• %i Prints an integer in base 10.										  */
/*	• %u Prints an unsigned decimal (base 10) number.						  */
/*	• %x Prints a number in hexadecimal (base 16) lowercase format.			  */
/*	• %X Prints a number in hexadecimal (base 16) uppercase format.			  */
/*	• %% Prints a percent sign                                                */
/*                                                                            */
/*  @param str  string a print contenant les expressions cspdiuxX%.           */
/*  @param ...  ce qui doit remplacer les expressions.                        */
/*  @return     0 / >0 if failed.                                             */
/*                                                                            */
/*  Example:                                                                  */
/*     ft_printf("(%d, %d)", arr[i], arr[j]);                                 */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

// \num    Write a byte whose value is the 1-,
// 			2-, or 3-digit octal number num.
// 			Multibyte characters can be
// 			constructed using multiple \num
// 			sequences.
static int	print_escape(char c)
{
	if (c == 'a')
		return (pf_putchar(7));
	else if (c == 'b')
		return (pf_putchar(8));
	else if (c == 'f')
		return (pf_putchar(12));
	else if (c == 'n')
		return (pf_putchar(10));
	else if (c == 'r')
		return (pf_putchar(13));
	else if (c == 't')
		return (pf_putchar(9));
	else if (c == 'v')
		return (pf_putchar(11));
	else if (c == 44)
		return (pf_putchar(44));
	else if (c == '\\')
		return (pf_putchar('\\'));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
			count += dispatch_conversion(*(++str), &ap);
		else if (*str == '\\')
			count += print_escape(*(++str));
		else
			count += pf_putchar(*str);
		str++;
	}
	va_end(ap);
	return (count);
}
