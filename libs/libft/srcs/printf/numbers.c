/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:31:46 by lgervet           #+#    #+#             */
/*   Updated: 2025/12/20 10:20:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*str0(char *str)
{
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*pf_itoa(int n, char *str, int base)
{
	int	i;
	int	is_negative;

	i = 0;
	is_negative = 0;
	if (n == 0)
		return (str0(str));
	if (n < 0)
	{
		if (base == 10)
			is_negative = 1;
		n = -n;
	}
	while (n != 0)
	{
		if ((n % base) > 9)
			str[i++] = (((n % base) - 10) + 'a');
		else
			str[i++] = ((n % base) + '0');
		n = n / base;
	}
	if (is_negative)
		str[i++] = '-';
	str[i] = '\0';
	return (pf_strrev(str));
}

char	*pf_uitoa(unsigned long long n, char *str, int base)
{
	int	i;

	i = 0;
	if (n == 0)
		return (str0(str));
	while (n != 0)
	{
		if ((n % base) > 9)
			str[i++] = (((n % base) - 10) + 'a');
		else
			str[i++] = ((n % base) + '0');
		n = n / base;
	}
	str[i] = '\0';
	return (pf_strrev(str));
}
