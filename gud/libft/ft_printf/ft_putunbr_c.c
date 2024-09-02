/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:43:38 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/19 21:11:23 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr_c(unsigned int n)
{
	int		len;

	len = ft_ulllen_base((unsigned long long)n, 10);
	ft_write_ull((unsigned long long)n, 10, DECIMAL);
	return (len);
}
