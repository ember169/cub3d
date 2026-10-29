/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:01:59 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	• %c Prints a single character.											  */
/*	• %s Prints a string (as defined by the common C convention).			  */
/*	• %p The void * pointer argument has to be printed in hexadecimal format. */
/*	• %d Prints a decimal (base 10) number.									  */
/*	• %i Prints an integer in base 10.										  */
/*	• %u Prints an unsigned decimal (base 10) number.						  */
/*	• %x Prints a number in hexadecimal (base 16) lowercase format.			  */
/*	• %X Prints a number in hexadecimal (base 16) uppercase format.			  */
/*	• %% Prints a percent sign                                                */

#include "includes/libft.h"

int	convert_char(va_list *ap)
{
	unsigned char	arg;

	arg = va_arg(*ap, int);
	return (pf_putchar(arg));
}

int	convert_str(char flag, va_list *ap)
{
	char	str[21];
	char	*s;
	int		count;

	count = 0;
	if (flag == 's')
	{
		s = va_arg(*ap, char *);
		if (!s)
			return (pf_putstr("(null)"));
		count += pf_putstr(s);
	}
	else if (flag == 'x')
	{
		pf_uitoa(va_arg(*ap, unsigned int), str, 16);
		count += pf_putstr(str);
	}
	else if (flag == 'X')
	{
		pf_uitoa(va_arg(*ap, unsigned int), str, 16);
		pf_toupper(str);
		count += pf_putstr(str);
	}
	return (count);
}

int	convert_num(char flag, va_list *ap)
{
	int					count;
	void				*ptr;
	unsigned long long	arg;
	char				str[21];

	count = 0;
	if (flag == 'd')
		count += pf_putnbr(va_arg(*ap, int));
	else if (flag == 'p')
	{
		ptr = va_arg(*ap, void *);
		if (!ptr)
			return (pf_putstr(NULL_PTR_STR));
		arg = (unsigned long long)ptr;
		pf_uitoa(arg, str, 16);
		count += pf_printmemaddress(str);
	}
	else if (flag == 'i')
		count += pf_putnbr(va_arg(*ap, int));
	else if (flag == 'u')
		count += pf_uputnbr(va_arg(*ap, unsigned int));
	return (count);
}

int	dispatch_conversion(char c, va_list *ap)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += convert_char(ap);
	else if (c == 's' || c == 'x' || c == 'X')
		count += convert_str(c, ap);
	else if (c == 'p')
		count += convert_num(c, ap);
	else if (c == 'd' || c == 'i' || c == 'u')
		count += convert_num(c, ap);
	else if (c == '%')
		count += pf_putchar('%');
	return (count);
}

/* gestions des futurs flags -0.# + */
