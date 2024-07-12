/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:47:48 by david             #+#    #+#             */
/*   Updated: 2024/07/12 00:52:21 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_err(int op, char *arg)
{
    char    *err;
    char    *err_aux;

    ft_putstr_fd("exit\n", 2);
	if (op == 1)
        ft_putstr_fd("bash: exit: too many arguments\n", 2);
    else if (op == 2)
    {
        err_aux = ft_strjoin2("bash: exit:", arg);
        err = ft_strjoin2(err_aux, ": numeric argument requiered\n");
        ft_putstr_fd(err, 2);
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

static void	ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

static int	ft_exittoi(char *s, t_mini *mini)
{
	int					i;
	int					sign;
	unsigned long	    result;

	i = 0;
	sign = 1;
	ft_skip_spaces_and_get_sign(s, &i, &sign);
	if (!ft_isnumber(s + i))
	{
		ft_err(2, s);
		ft_free_all(mini);
        exit(255);
	}
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > 2147483647) //Tener en cuenta el signo? 2147483648 si signo = -?
		{
			ft_err(2, s);
			ft_free_all(mini);
            exit(255);
		}
		i++;
	}
	return ((result * sign) % 256);
}

void	ft_exit(char *str_arg, t_mini *mini)
{
    int     exit_num;
    char    **args;

    exit_num = 0;
	args = ft_split(str_arg, ' ');
	if (args[1])
	{
		if (args[2] && ft_isnumber(args[1]))
		{
			ft_err(1, "error");
			ft_free_all(mini);
            exit(1);
		}
		else
			exit_num = ft_exittoi(args[1], mini);
	}
	ft_free_all(mini);
    exit(exit_num);
}