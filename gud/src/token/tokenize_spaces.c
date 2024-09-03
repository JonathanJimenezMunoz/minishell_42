/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:03:28 by david             #+#    #+#             */
/*   Updated: 2024/09/03 15:18:41 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	tokenize_space(char **line, t_mini *mini)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*line)[i] && !ft_isspace((*line)[i]))
	{
		i++;
	}
	if (i > 0)
	{
		tmp = (char *)malloc(sizeof(char) * (2));
		if (!tmp)
			return ;
		tmp[0] = ' ';
		tmp[1] = '\0';
		ft_add_token(TOKEN_SPACE, &tmp, mini, 1);
		tmp--;
		free(tmp);
		*line += i;
	}
}
