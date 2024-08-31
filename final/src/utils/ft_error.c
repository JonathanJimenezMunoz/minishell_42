/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:56:21 by david             #+#    #+#             */
/*   Updated: 2024/08/31 15:18:03 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_error(t_mini *mini, char *error, char *type, int exit)
{
	if (mini->error == 0)
	{
		printf("bash: %s `%s'\n", error, type);
		mini->error = 1;
	}
	mini->exit_status = exit;
}