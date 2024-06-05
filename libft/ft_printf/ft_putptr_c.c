/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:40:06 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/19 21:11:05 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr_c(void *ptr)
{
	unsigned long long	p;
	int					len;

	p = (unsigned long long)ptr;
	len = ft_ulllen_base(p, 16);
	ft_putstr_c("0x");
	len += 2;
	ft_write_ull(p, 16, HEX_LOW);
	return (len);
}
