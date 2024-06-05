/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:45:20 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/15 22:00:39 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	pos1;
	size_t	pos2;
	size_t	len_src;

	pos2 = 0;
	pos1 = 0;
	len_src = 0;
	while (src[len_src] != '\0')
		len_src++;
	while (dst[pos1] != '\0')
		pos1++;
	if (size == 0 || size <= pos1)
		return (len_src + size);
	while (src[pos2] != '\0' && size > (pos1 + 1))
	{
		dst[pos1] = src[pos2];
		pos2++;
		pos1++;
	}
	dst[pos1] = '\0';
	return ((pos1 - pos2) + len_src);
}
