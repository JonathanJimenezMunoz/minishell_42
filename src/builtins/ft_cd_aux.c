/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:48:42 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/10/15 18:49:14 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_explicit_error(char *path)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	ft_home_virgulilla(t_envp *envp, char *path)
{
	char	*home;
	char	*new_path;

	home = envp_get_value(envp, "HOME");
	if (!home)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (1);
	}
	new_path = ft_strjoin(home, path + 1);
	if (!new_path)
	{
		ft_explicit_error(path);
		return (1);
	}
	if (chdir(new_path) == -1)
	{
		ft_explicit_error(path);
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

int	ft_home_path(t_envp *envp)
{
	char	*path;

	path = envp_get_value(envp, "HOME");
	if (!path)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}
