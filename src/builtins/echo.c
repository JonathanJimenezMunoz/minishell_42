/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:18:15 by david             #+#    #+#             */
/*   Updated: 2024/07/08 23:23:25 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_echo(char *args)
{
	int	opt;

	opt = 0;
	if (args[0] != '-' || args[1] != 'n')
	{
		opt = 1;
		ft_putstr_fd(args + 3, 1);
	}
	else
        ft_putstr_fd(args, 1);
	if (opt == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}