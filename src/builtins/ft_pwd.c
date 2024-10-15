/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonjimen <jonjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:18:25 by david             #+#    #+#             */
/*   Updated: 2024/10/15 16:45:49 by jonjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(void)
{
	char	*route;

	route = NULL;
	route = getcwd(route, 0);
	if (!route)
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(route, 1);
	ft_putstr_fd("\n", 1);
	free(route);
	return (0);
}
