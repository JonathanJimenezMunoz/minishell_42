/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:57:45 by david             #+#    #+#             */
/*   Updated: 2024/08/21 17:12:25 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	pos;
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (n < len)
		len = n;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	pos = 0;
	while (s[pos] != '\0' && pos < len)
	{
		result[pos] = s[pos];
		pos++;
	}
	result[pos] = '\0';
	return (result);
}
