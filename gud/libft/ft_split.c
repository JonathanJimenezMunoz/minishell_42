/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:08:30 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/16 16:09:59 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_stringcount(char *str, char sep)
{
	int	i;
	int	counter;
	int	new_string;

	new_string = 1;
	counter = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sep)
			new_string = 1;
		else
		{
			if (new_string == 1)
			{
				counter++;
				new_string = 0;
			}
		}
		i++;
	}
	return (counter);
}

static char	*put_string(char *str, char charset)
{
	int		len;
	char	*string;
	int		i;

	len = 0;
	i = 0;
	while (str[len] != '\0' && *(str + len) != charset)
		len++;
	string = (char *)malloc(sizeof(char) * (len + 1));
	if (!string)
		return (0);
	while (i < len)
	{
		string[i] = str[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static char	*process_string(char **sol, char *str, char charset, int i)
{
	sol[i] = put_string(str, charset);
	if (!sol[i])
	{
		while (i >= 0)
		{
			free(sol[i]);
			i--;
		}
		free(sol);
		return (0);
	}
	return (str);
}

static char	**ft_split_aux(char **sol, char *str, char charset)
{
	int	i;
	int	new_string;

	new_string = 1;
	i = 0;
	while (*str != '\0')
	{
		if (*str == charset)
			new_string = 1;
		else
		{
			if (new_string == 1)
			{
				str = process_string(sol, str, charset, i);
				if (!str)
					return (0);
				i++;
				new_string = 0;
			}
		}
		str++;
	}
	sol[i] = 0;
	return (sol);
}

char	**ft_split(char const *s, char c)
{
	char	**sol;
	char	*copy;

	copy = ft_strdup(s);
	if (!copy)
		return (0);
	sol = malloc(sizeof(char *) * (ft_stringcount(copy, c) + 1));
	if (!sol)
	{
		free(copy);
		return (0);
	}
	sol = ft_split_aux(sol, copy, c);
	free(copy);
	return (sol);
}
