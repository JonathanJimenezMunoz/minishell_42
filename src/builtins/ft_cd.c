/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:46:27 by david             #+#    #+#             */
/*   Updated: 2024/10/15 18:49:27 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	change_env_oldpwd(t_envp *envp, char *key)
{
	char	*oldpwd;

	if (ft_strcmp(key, "OLDPWD") == 0)
	{
		oldpwd = envp_get_value(envp, "PWD");
		if (oldpwd)
			update_or_add_env(&envp, key, oldpwd);
	}
}

static void	change_env_pwd(t_envp *envp, char *path, char *key)
{
	char	*pwd;
	char	*new_pwd;
	char	*temp_pwd;

	new_pwd = NULL;
	temp_pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("bash: cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access ", 2);
		ft_putstr_fd("parent directories: No such file or directory\n", 2);
		if (path[0] != '/')
			temp_pwd = ft_strjoin("/", path);
		new_pwd = ft_strjoin(envp_get_value(envp, key), temp_pwd);
		if (new_pwd)
			update_or_add_env(&envp, key, new_pwd);
		free(temp_pwd);
		return ;
	}
	if (ft_strcmp(key, "PWD") == 0)
		update_or_add_env(&envp, key, pwd);
	free(pwd);
}

int	ft_cd(char **paths, t_envp *envp)
{
	if (!paths[0] || !paths[1])
		return (ft_home_path(envp));
	else if (paths[1][0] == '~')
		return (ft_home_virgulilla(envp, paths[1]));
	if (paths[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return (1);
	}
	if (access(paths[1], F_OK) != -1)
		change_env_oldpwd(envp, "OLDPWD");
	if (chdir(paths[1]) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(paths[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	change_env_pwd(envp, paths[1], "PWD");
	return (0);
}
