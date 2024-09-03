/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:24:08 by david             #+#    #+#             */
/*   Updated: 2024/09/03 15:53:13 by dyanez-m         ###   ########.fr       */
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

void	ft_dputstr_fd(char *s1, char *s2, int fd, int error)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	tmp = ft_strjoin("bash :", s1);
	tmp2 = ft_strjoin(tmp, ": ");
	tmp3 = ft_strjoin(tmp2, s2);
	tmp4 = ft_strjoin(tmp3, "\n");
	write(fd, tmp4, ft_strlen(tmp4));
	free(tmp);
	free(tmp2);
	free(tmp3);
	free(tmp4);
	exit(error);
}
