/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:47:48 by david             #+#    #+#             */
/*   Updated: 2024/10/15 18:38:52 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_err(int op, char *arg, t_mini *mini)
{
	char	*err;
	char	*err_aux;

	if (op == 1)
	{
		if (mini->pipes == 1)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
	}
	else if (op == 2)
	{
		if (mini->pipes == 1)
			ft_putstr_fd("exit\n", 2);
		err_aux = ft_strjoin("bash: exit: ", arg);
		err = ft_strjoin2(err_aux, ": numeric argument required\n");
		ft_putstr_fd(err, 2);
		free(err);
	}
}

static int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_skip_spaces_and_get_sign(char *s, int *i,
	int *sign, t_mini *mini)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
	if (!ft_isnumber(s + (*i)))
	{
		ft_err(2, s, mini);
		ft_free_all(mini);
		exit(2);
	}
}

static int	ft_exittoi(char *s, t_mini *mini)
{
	int					i;
	int					sign;
	unsigned long		result;

	i = 0;
	sign = 1;
	ft_skip_spaces_and_get_sign(s, &i, &sign, mini);
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > 2147483647)
		{
			ft_err(2, s, mini);
			ft_free_all(mini);
			exit(2);
		}
		i++;
	}
	return ((result * sign) % 256);
}

int	ft_exit(char **args, t_mini *mini)
{
	int	exit_num;

	exit_num = 0;
	if (args && args[1])
	{
		if (args[2] && ft_isnumber(args[1]))
		{
			ft_err(1, "error", mini);
			return (1);
		}
		else
			exit_num = ft_exittoi(args[1], mini);
	}
	ft_free_all(mini);
	if (mini->pipes == 1)
		ft_putstr_fd("exit\n", 2);
	if (exit_num == 0)
		exit(mini->exit_status);
	exit(exit_num);
	return (0);
}
