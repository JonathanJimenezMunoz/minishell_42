/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:33:48 by david             #+#    #+#             */
/*   Updated: 2024/08/21 17:13:00 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	int	pos;

	pos = 0;
	if (str == 0)
		return (0);
	while (str[pos] != '\0')
		pos++;
	return (pos);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (free_return(&s1));
	while (s1 && s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
	{
		result[j + i] = s2[j];
		j++;
	}
	free(s1);
	result[i + j] = '\0';
	return (result);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	pos;
	size_t	len_m;

	pos = 0;
	len_m = ft_strlen_gnl(s);
	if (s == 0)
		return (0);
	if (start >= len_m)
		return (ft_strdup_gnl(""));
	if (len > len_m - start)
		len = len_m - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == 0)
		return (0);
	while (s[start + pos] != '\0' && len > pos)
	{
		sub[pos] = s[start + pos];
		pos++;
	}
	sub[pos] = '\0';
	return (sub);
}

char	*ft_strdup_gnl(const char *s1)
{
	int		len;
	char	*copy;

	len = 0;
	while (s1[len] != '\0')
		len++;
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == 0)
		return (0);
	len = 0;
	while (s1[len] != '\0')
	{
		copy[len] = s1[len];
		len++;
	}
	copy[len] = '\0';
	return (copy);
}
