/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:56:21 by david             #+#    #+#             */
/*   Updated: 2024/09/03 15:29:52 by dyanez-m         ###   ########.fr       */
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

void	ft_error_syx(t_mini *mini, char *type, int exit)
{
	if (mini->error == 0)
	{
		printf("bash: syntax error near unexpected token `%s'\n", type);
		mini->error = 1;
	}
	mini->exit_status = exit;
}
