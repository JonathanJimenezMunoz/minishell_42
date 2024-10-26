/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:56:21 by david             #+#    #+#             */
/*   Updated: 2024/10/20 19:12:59 by dyanez-m         ###   ########.fr       */
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

void	ft_dputstr_fd(char *s1, char *s2, int fd, int error)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	if (s1[0] == '\0')
		s1 = "''";
	tmp = ft_strjoin("bash: ", s1);
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

void	ft_ctrld_error(char *s1)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(
		"warning: here-document delimited by end-of-file (wanted ", 2);
	ft_putstr_fd(s1, 2);
	ft_putendl_fd(")", 2);
	free(s1);
	exit(0);
}

void	ft_error_export(char *args)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(args, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
