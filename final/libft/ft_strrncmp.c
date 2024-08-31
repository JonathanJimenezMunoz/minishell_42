/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:46:14 by david             #+#    #+#             */
/*   Updated: 2023/11/07 01:14:56 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//funcion para comprobar los ultimos n caracteres de dos strings
/*Esta funcion se creo para hacer el so_long no se recomienda su uso
Para otras funciones pues no es totalmente robusta*/
static int	ft_helper(const char *end1, const char *end2, size_t n)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(end1);
	len2 = ft_strlen(end2);
	if (n > len1)
		n = len1;
	if (n > len2)
		n = len2;
	return (n);
}

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	const char	*end1;
	const char	*end2;

	if ((s1 == NULL || s1[0] == '\0') && (s2 == NULL || s2[0] == '\0'))
		return (0);
	if (s1 == NULL || s1[0] == '\0' || s2 == NULL || s2[0] == '\0')
		return (1);
	end1 = s1 + ft_strlen(s1) - 1;
	end2 = s2 + ft_strlen(s2) - 1;
	n = ft_helper(s1, s2, n);
	while (n > 0)
	{
		if (*end1 != *end2)
		{
			return ((unsigned char)(*end1) - (unsigned char)(*end2));
		}
		n--;
		end1--;
		end2--;
	}
	return (0);
}
