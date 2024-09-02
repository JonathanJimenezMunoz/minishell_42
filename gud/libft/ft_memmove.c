/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:27:56 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/18 10:40:57 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned char		*des;
	unsigned const char	*sr;
	int					nb;

	nb = (int)n;
	sr = (unsigned const char *)src;
	des = (unsigned char *)dest;
	if (dest == 0 && src == 0)
		return (0);
	if (dest < src)
	{
		i = -1;
		while (++i < nb)
			des[i] = sr[i];
	}
	else
	{
		i = nb;
		while (--i >= 0)
			des[i] = sr[i];
	}
	return (dest);
}
