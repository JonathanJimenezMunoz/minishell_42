/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:18:25 by david             #+#    #+#             */
/*   Updated: 2024/08/21 17:05:22 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(void)
{
	char	*route;

	route = NULL;
	route = getcwd(route, 0);
	if (!route)
		return (-1);
	ft_putstr_fd(route, 1);
	ft_putstr_fd("\n", 1);
	free(route);
	return (0);
}
