/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonjimen <jonjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:18:15 by david             #+#    #+#             */
/*   Updated: 2024/10/15 16:50:29 by jonjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_skip_n(char **args)
{
	int	opt;
	int	j;
	int	end;

	opt = 1;
	j = 0;
	end = 1;
	while (end)
	{
		if (end && args[opt] && ft_strlen(args[opt]) >= 2
			&& args[opt][j] == '-')
		{
			j++;
			while (args[opt][j] && args[opt][j] == 'n')
				j++;
			if (args[opt][j])
				end = 0;
			else
				opt++;
			j = 0;
		}
		else
			end = 0;
	}
	return (opt);
}

int	ft_echo(char **args)
{
	int		opt;
	char	*joined_args;

	if (!args || !args[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	opt = ft_skip_n(args);
	joined_args = join_strs(&(args[opt]));
	if (joined_args)
	{
		ft_putstr_fd(joined_args, 1);
		free(joined_args);
	}
	if (opt == 1)
		ft_putstr_fd("\n", 1);
	return (0);
}
