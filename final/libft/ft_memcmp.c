/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:15:44 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/15 22:00:04 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s3;
	const unsigned char	*s4;
	int					i;

	i = 0;
	s3 = s1;
	s4 = s2;
	while (n > 0 && (s3[i] == s4[i]))
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s3[i] - (unsigned char)s4[i]);
}
