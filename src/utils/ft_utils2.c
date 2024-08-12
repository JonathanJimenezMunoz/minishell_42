/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:43:01 by david             #+#    #+#             */
/*   Updated: 2024/08/12 20:32:57 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_redir_type(char **line, t_mini *mini)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (ft_add_token(TOKEN_REDIR_DELIMITER, line, mini, 2));
	else if (!ft_strncmp(*line, ">>", 2))
		return (ft_add_token(TOKEN_REDIR_APPEND, line, mini, 2));
	else if (!ft_strncmp(*line, "<", 1))
		return (ft_add_token(TOKEN_REDIR_IN, line, mini, 1));
	else if (!ft_strncmp(*line, ">", 1))
		return (ft_add_token(TOKEN_REDIR_OUT, line, mini, 1));
	else if (!ft_strncmp(*line, "|", 1))
		return (ft_add_token(TOKEN_PIPE, line, mini, 1));
	else
		return (-1);
}

void	open_file(char *file, int flags, int mode, t_mini *mini)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(file);
		write_file(".err", 1);
		mini->status = 1;
	}
}
char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	return (envp[i] + 5);
}

char	*join_args(char **args)
{
	char	*result;
	char	*temp;
	int		i;

	i = 1;
	if (!args || !args[0])
		return (NULL);
	result = ft_strdup(args[0]);
	if (!result)
		return (NULL);
	while(args[i])
	{
		temp = ft_strjoin(result, " ");
		free(result);
		if (!temp)
			return (NULL);
		result = ft_strjoin(temp, args[i]);
		free(temp);
		if (!result)
			return (NULL);
	}
	return (result);
}