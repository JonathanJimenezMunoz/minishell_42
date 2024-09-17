/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:46:27 by david             #+#    #+#             */
/*   Updated: 2024/09/01 15:59:46 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_home_path(t_envp *envp)
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

int	ft_cd(char **paths, t_envp *envp)
{
	if (!paths[0] || !paths[1])
		return (ft_home_path(envp));
	else
	{
		if (paths[2])
		{
			ft_putstr_fd("bash: cd: too many arguments\n", 2);
			return (1);
		}
		else if (chdir(paths[1]) == -1)
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(paths[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		return (0);
	}
}
