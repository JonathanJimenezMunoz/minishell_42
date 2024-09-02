/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:01:52 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/16 13:02:08 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int			i;
	char		*des;
	const char	*sr;

	if (dest == 0 && src == 0)
		return (0);
	des = dest;
	sr = src;
	i = 0;
	while (n > 0)
	{
		des[i] = sr[i];
		n--;
		i++;
	}
	return (dest);
}
