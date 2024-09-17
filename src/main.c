/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:40:23 by david             #+#    #+#             */
/*   Updated: 2024/09/14 20:29:03 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int g_sigint;

static void	init_mini(t_mini *mini, char **envp)
{
	mini->line = NULL;
	mini->tokens = NULL;
	mini->table = NULL;
	mini->envp = NULL;
	mini->exit_status = 0;
	mini->error = 0;
	mini->flag_redir = 0;
	mini->exec_envp = NULL;
	envp_init(&mini->envp, envp);
	mini->exec_envp = copy_double_str(envp);
}

static void	iteration_handler(t_mini *mini)
{
	free_token_list(&mini->tokens);
	free_table(&mini->table);
	free(mini->line);
	mini->line = NULL;
	mini->tokens = NULL;
	mini->table = NULL;
	mini->error = 0;
	mini->pipes = 0;
	mini->flag_redir = 0;
}

void	print_redirections(t_redir *redir)
{
	while (redir != NULL)
	{
		printf("\tRedirection: File = %s, Type = %d\n",
			redir->file, redir->type);
		redir = redir->next;
	}
}

void	print_table(t_table *table)
{
	int i;

	while (table != NULL)
	{
		printf("Args:\n");
		if (table->args != NULL)
		{
			for (i = 0; table->args[i] != NULL; i++)
			{
				printf("\t%s\n", table->args[i]);
			}
		}
		if (table->redir != NULL)
		{
			print_redirections(table->redir);
		}
		table = table->next;
		printf("\n");
	}
}

static void do_redir_handler(t_mini *mini)
{
	t_table	*table_aux;
	t_redir	*redir_aux;

	table_aux = mini->table;
	while (table_aux)
	{
		mini->flag_redir = 0;
		redir_aux = table_aux->redir;
		while (redir_aux)
		{
			if ((redir_aux->type == TOKEN_REDIR_IN || redir_aux->type == TOKEN_UNLINK) && mini->flag_redir == 0)
				open_input_file(redir_aux->file, mini);
			else if (redir_aux->type == TOKEN_REDIR_OUT
				&& mini->flag_redir == 0)
				open_output_file(redir_aux->file, mini, 0);
			else if (redir_aux->type == TOKEN_REDIR_APPEND
				&& mini->flag_redir == 0)
				open_output_file(redir_aux->file, mini, 1);
			redir_aux = redir_aux->next;
		}
		table_aux = table_aux->next;
	}
}

static void	ft_loop(t_mini *mini)
{
	while (1)
	{
		while_signals(mini);
		mini->line = readline("msh>>");
		if (!mini->line)
		{
			printf("msh>>exit\n");
			ft_free_all(mini);
			exit(mini->exit_status);
		}
		add_history(mini->line);
		tokenize_line(mini->line, mini);
		if (mini->error == 0)
		{
			parser_token(mini);
			ft_check_if_heredoc(mini);
			do_redir_handler(mini);
		}
		if (mini->error == 0)
			execute(mini);
		iteration_handler(mini);
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init_mini(&mini, envp);
	ft_loop(&mini);
}
