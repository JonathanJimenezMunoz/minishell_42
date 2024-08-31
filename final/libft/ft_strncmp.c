/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:40:04 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/15 22:01:04 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	pos;

	pos = 0;
	while (s1[pos] != '\0' && s2[pos] != '\0' && s1[pos] == s2[pos] && n > 0)
	{
		pos++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}
