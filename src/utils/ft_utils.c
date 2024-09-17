/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:24:08 by david             #+#    #+#             */
/*   Updated: 2024/09/15 12:45:01 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (0);
	return (-1);
}

int	ft_is_good_quote(char *line)
{
	int		i;
	char	quote_type;

	if (!line)
		return (-1);
	i = 0;
	if (line[i] == '\'' || line[i] == '\"')
		quote_type = line[i];
	else
		return (-2);
	i++;
	while (line[i])
	{
		if (line[i] == quote_type)
			return (i - 1);
		i++;
	}
	return (-1);
}

int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*heredoc_filename(void)
{
	static int	i;
	char		*num;
	char		*file;

	num = ft_itoa(i++);
	file = ft_strjoin(".heredoc_", num);
	free(num);
	return (file);
}
