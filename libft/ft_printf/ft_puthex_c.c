/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:02:00 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/19 21:15:24 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_c(unsigned int n, int up)
{
	int		len;

	len = ft_ulllen_base((unsigned long long)n, 16);
	if (up == 1)
		ft_write_ull((unsigned long long)n, 16, HEX_UP);
	else
		ft_write_ull((unsigned long long)n, 16, HEX_LOW);
	return (len);
}
