/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_basics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:37:05 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	pf_putchar(char c)
{
	return (write(1, &c, 1));
}

int	pf_putstr(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = pf_strlen(str);
	write(1, str, len);
	return (len);
}

int	pf_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (count += pf_putstr("-2147483648"));
	if (n < 0)
	{
		count += pf_putchar('-');
		n = -n;
	}
	if (n < 10)
	{
		count += pf_putchar('0' + n);
		return (count);
	}
	else if (n > 9)
	{
		count += pf_putnbr(n / 10);
		count += pf_putchar('0' + (n % 10));
	}
	return (count);
}

int	pf_uputnbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n < 10)
	{
		count += pf_putchar('0' + n);
		return (count);
	}
	else if (n > 9)
	{
		count += pf_uputnbr(n / 10);
		count += pf_putchar('0' + (n % 10));
	}
	return (count);
}

int	pf_printmemaddress(char *str)
{
	int	i;

	i = 0;
	i += pf_putstr("0x");
	i += pf_putstr(str);
	return (i);
}
