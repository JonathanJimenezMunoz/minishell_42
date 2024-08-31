/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:23:33 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/19 20:02:08 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type(const char *str, va_list args)
{
	int	len;

	len = 0;
	if (*str == 'c')
		len += ft_putchar_c(va_arg(args, int));
	else if (*str == 's')
		len += ft_putstr_c(va_arg(args, char *));
	else if (*str == 'p')
		len += ft_putptr_c(va_arg(args, void *));
	else if (*str == 'd' || *str == 'i')
		len += ft_putnbr_c(va_arg(args, int));
	else if (*str == 'u')
		len += ft_putunbr_c(va_arg(args, unsigned int));
	else if (*str == 'x')
		len += ft_puthex_c(va_arg(args, unsigned int), 0);
	else if (*str == 'X')
		len += ft_puthex_c(va_arg(args, unsigned int), 1);
	else if (*str == '%')
		len += ft_putchar_c('%');
	return (len);
}

int	ft_printf(const char *string, ...)
{
	int		i;
	va_list	args;
	int		counter;

	i = 0;
	counter = 0;
	if (!string)
		return (0);
	va_start(args, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			counter += ft_type((string + i), args);
		}
		else
		{
			ft_putchar_fd(*(string + i), 1);
			counter++;
		}
		i++;
	}
	va_end(args);
	return (counter);
}
