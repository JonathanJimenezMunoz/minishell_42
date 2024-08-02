/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:18:15 by david             #+#    #+#             */
/*   Updated: 2024/08/02 23:55:19 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


int ft_echo(char **args)
{
	int opt;
	char *joined_args;

	opt = 0;
	if (!args || !args[0])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (ft_strlen(args[0]) >= 2 && args[0][0] == '-' && args[0][1] == 'n')
	{
		opt = 1;
		args++;
	}
	joined_args = join_args(args);
	if (joined_args)
	{
		ft_putstr_fd(joined_args, 1);
		free(joined_args);
	}
	if (opt == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
/*int	ft_echo(char **args)
{
	int	opt;

	opt = 0;
	if (!args)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	
	if (ft_strlen(args) >= 2 && args[0] == '-' && args[1] == 'n')
	{
		opt = 1;
		if (ft_strlen(args) >= 3 && args[2] == ' ')
			args += 3;
		else
			args += 2;
		ft_putstr_fd(args, 1);
	}
	else
        ft_putstr_fd(args, 1);
	if (opt == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}*/
