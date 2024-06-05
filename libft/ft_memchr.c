/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:12:08 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/15 21:59:39 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*aux;
	int					i;
	unsigned char		p;

	p = (unsigned char)c;
	i = 0;
	aux = s;
	while (n > 0)
	{
		if (aux[i] == p)
			return ((void *)(aux + i));
		i++;
		n--;
	}
	return (0);
}
