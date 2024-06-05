/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:33:48 by david             #+#    #+#             */
/*   Updated: 2023/11/08 00:46:49 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr2(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		s1 = ft_calloc2(1, sizeof(char));
	result = (char *)malloc(sizeof(char) * (ft_strlen2(s1) + ft_strlen2(s2) + 1));
	if (!result)
		return (0);
	while (s1[++i] != '\0')
		result[i] = s1[i];
	while (s2[++j] != '\0')
		result[i++] = s2[j];
	result[i] = '\0';
	free(s1);
	return (result);
}

size_t	ft_strlen2(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

void	*ft_calloc2(size_t nmemb, size_t size)
{
	void	*array;

	array = (void *)malloc(size * nmemb);
	if (array != NULL)
		ft_bzero2(array, nmemb * size);
	return (array);
}

void	ft_bzero2(void *s, size_t n)
{
	unsigned char	*aux;
	int				i;

	i = 0;
	aux = s;
	while (n > 0)
	{
		aux[i] = '\0';
		n--;
		i++;
	}
}
