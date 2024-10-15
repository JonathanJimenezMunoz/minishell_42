/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:18:25 by david             #+#    #+#             */
/*   Updated: 2024/10/15 18:22:04 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	*route;
	char	*alt_route;

	alt_route = NULL;
	route = NULL;
	route = getcwd(route, 0);
	if (!route)
	{
		alt_route = envp_get_value(mini->envp, "PWD");
		if (!alt_route)
		{
			perror(route);
			return (1);
		}
		else
		{
			ft_putstr_fd(alt_route, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
	}
	ft_putstr_fd(route, 1);
	ft_putstr_fd("\n", 1);
	free(route);
	return (0);
}
