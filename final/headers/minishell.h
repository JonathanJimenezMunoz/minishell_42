/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:50:07 by david             #+#    #+#             */
/*   Updated: 2024/09/02 17:35:37 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"

extern int	g_sigint;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_DELIMITER,
	TOKEN_SPACE,
}	t_token_type;

typedef struct s_token
{
	char				*content;
	t_token_type		type;
	struct s_token		*next;
}	t_token;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef	struct s_table
{
	char			**args;
	char			**in_redir;
	char			**out_redir;
	char			**in_heredoc;
	char			**out_append;	
	char			*last_out_redir;
	int				append;
	struct s_table	*next;
}	t_table;

typedef struct s_table_aux
{
	char	**args;
	char	**in_redir;
	char	**out_redir;
	char	**in_heredoc;
	char	*last_out_redir;
	char	**out_append;
	int		append;
}	t_table_aux;

typedef struct s_mini
{
	t_token	*tokens;
	t_table	*table;
	t_envp	*envp;
	char	**exec_envp;
	int		exit_status;
	char	*line;
	int		error;
	int		pipes;
}	t_mini;

// BUILTINS
int		ft_cd(char **paths, t_envp *envp);
int		ft_export(char **args, t_envp **envp);
int		ft_unset(char **args, t_mini *mini);
int		ft_exit(char **args, t_mini *mini);
int		ft_echo(char **args);
int		ft_envp(t_envp *envp);
int		ft_pwd(void);

// ENVP
void	envp_init(t_envp **envp, char **envp_list);
char	*envp_get_value(t_envp *envp, char *key);
void	envp_print(t_envp *envp);
void	add_node_to_envp(t_envp **envp, t_envp *new_node);
void	swap(t_envp *a, t_envp *b);
void	sort_envp(t_envp *envp);
t_envp	*copy_envp_list(t_envp *envp);
void	free_envp_list(t_envp *envp);
void	print_envp_declare(t_envp *envp);


// UTILS
char	**copy_double_str(char **str);
int		ft_isspace(char c);
int		ft_is_good_quote(char *line);
int		ft_intlen(int n);
void	*ft_realloc_double_array(void *ptr, size_t original_size, size_t new_size);
void	open_input_file(char *file_name, t_mini *mini);
void	open_output_file(char *file_name, t_mini *mini, int control);
char	*join_strs(char **args);
int		count_double_str(char **args);
char	*get_path(char **envp);
int		is_valid_identifier(const char *key);
int		ft_count_pipes(t_mini *mini);

// ERROR
void	ft_error(t_mini *mini, char *error, char *type, int exit);
void	ft_error_syx(t_mini *mini, char *type, int exit);

// FREE
void	free_double_array(char **str);
void	ft_free_all(t_mini *mini);
void	free_table_aux(t_table_aux *aux);
void	free_table(t_table **table);
void	free_token_list(t_token **token);

// TOKENIZE
int		tokenize_line(char *line, t_mini *mini);
char	*ft_new_line(char *line, int size, t_mini *mini);
void	tokenize_space(char **line, t_mini *mini);
int		ft_add_token(t_token_type type, char **line, t_mini *mini, int size);
void	join_token(t_token **tokens);

// PARSER
int		parser_token(t_mini *mini);
void	parse_args(t_table_aux *aux, t_token **current);
void	parse_redir_heredoc(t_mini *mini, t_table_aux *aux, t_token **current);
void	parse_redir_in(t_mini *mini, t_table_aux *aux, t_token **current);
void	parser_redir_out(t_mini *mini, t_table_aux *aux, t_token **current);
void	parse_redir_append(t_mini *mini, t_table_aux *aux, t_token **current);
int		add_node(t_mini **head, t_table_aux *aux);

//EXECUTE
void	process_heredoc(t_mini *mini);
void	do_redir_handler(t_mini *mini);
int		execute(t_mini *mini);
void	handle_output_append_redirection(const char *out_append);
void	handle_output_redirection(const char *out_redir);
void	handle_input_redirection(const char *in_redir);
void	execute_command(t_table *table_aux, t_mini *mini);
int		ft_individual_builtins(t_table *table_aux, t_mini *mini);
int		ft_non_individual_builtins(t_table *table_aux, t_mini *mini);
void	handle_redirection(t_table *table_aux);

//SIGNALS
void	sig_heredoc(int sig);
void	exit_capture(t_mini *mini, int status);
void	redir_exit_capture(t_mini *mini, int status, int *first);
void	while_signals(t_mini *mini);

// TEMPORALES
void	token_print(t_token *tokens);
void	print_table(t_table *table);

# endif