/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:08:04 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/11/08 00:53:28 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	int		pos;

	if (!s)
		return (0);
	pos = ft_strlen(s);
	result = (char *)malloc((pos + 1) * sizeof(char));
	if (!result)
		return (0);
	pos = 0;
	while (s[pos] != '\0')
	{
		result[pos] = s[pos];
		pos++;
	}
	result[pos] = '\0';
	return (result);
}
