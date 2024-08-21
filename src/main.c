/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:04:34 by david             #+#    #+#             */
/*   Updated: 2024/08/21 17:31:02 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <valgrind/memcheck.h>

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	setup_signal_handlers(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	init_mini(t_mini *mini)
{
	mini->tokens = NULL;
	mini->table = NULL;
	mini->error = NULL;
	mini->status = 0;
	mini->pipe_fd[0] = -1;
	mini->pipe_fd[1] = -1;
	mini->in_fd = STDIN_FILENO;
	mini->out_fd = STDOUT_FILENO;
}

//     #include <valgrind/memcheck.h>
//		VALGRIND_DO_LEAK_CHECK;
//		METER ESTO ENTRE LA 70 Y 71
static void	ft_loop(t_mini *mini, char **envp)
{
	char	*line;

	while (1)
	{
		line = readline("\033[92mmsh>>\033[0m");
		if (line == NULL)
		{
			printf("\033[92mmsh>>\033[0mexit\n");
			ft_free_all(mini);
			exit(1);
		}
		add_history(line);
		tokenize_line(line, mini);
		free(line);
		if (mini->status == 0)
			parser_token(mini);
		if (mini->status == 0)
			execute(mini, envp);
		ft_free_iteration(mini);
		init_mini(mini);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init_mini(&mini);
	mini.envp = NULL;
	envp_init(&mini.envp, envp);
	setup_signal_handlers();
	ft_loop(&mini, envp);
	return (0);
}
