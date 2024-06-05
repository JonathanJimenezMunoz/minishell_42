/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:44:41 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/19 21:04:02 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_write_ull(unsigned long long p, int base_len, char *base)
{
	if (p >= (unsigned long long)base_len)
	{
		ft_write_ull(p / base_len, base_len, base);
		ft_write_ull(p % base_len, base_len, base);
	}
	else
	{
		ft_putchar_c(base[p]);
	}
}

int	ft_ulllen_base(unsigned long long n, int base_len)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base_len;
		i++;
	}
	return (i);
}
