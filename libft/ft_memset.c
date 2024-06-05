/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:00:36 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/15 22:00:18 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*aux;
	int				i;

	aux = s;
	i = 0;
	while (n > 0)
	{
		aux[i] = (unsigned char)c;
		n--;
		i++;
	}
	return (s);
}
