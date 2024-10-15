/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:50:07 by david             #+#    #+#             */
/*   Updated: 2024/10/15 19:06:20 by dyanez-m         ###   ########.fr       */
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
	TOKEN_EMPTY,
	TOKEN_UNLINK,
	TOKEN_QUOTES_EMPTY,
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

typedef struct s_redir
{
	char			*file;
	t_token_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_table
{
	char			**args;
	t_redir			*redir;
	struct s_table	*next;
}	t_table;

typedef struct s_table_aux
{
	char	**args;
	t_redir	*redir;
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
	int		flag_redir;
}	t_mini;

// BUILTINS
int		ft_cd(char **paths, t_envp *envp);
int		ft_home_path(t_envp *envp);
int		ft_home_virgulilla(t_envp *envp, char *path);
int		ft_export(char **args, t_envp **envp);
int		update_or_add_env(t_envp **envp, char *key, char *value);
int		ft_unset(char **args, t_mini *mini);
int		ft_exit(char **args, t_mini *mini);
int		ft_echo(char **args);
int		ft_envp(t_envp *envp, char **args);
int		ft_pwd(t_mini *mini);

// ENVP
void	envp_init(t_envp **envp, char **envp_list);
char	*envp_get_value(t_envp *envp, char *key);
void	add_node_to_envp(t_envp **envp, t_envp *new_node);
void	swap(t_envp *a, t_envp *b);
void	sort_envp(t_envp *envp);
t_envp	*copy_envp_list(t_envp *envp);
void	free_envp_list(t_envp *envp);
void	update_exec_envp_to_envp(t_mini *mini);
void	check_if_shlvl(t_envp **mini);
void	print_envp_declare(t_envp *envp);
void	handle_redirection_export(t_envp *envp, t_table *table_aux,
			t_mini *mini);

// UTILS
char	**copy_double_str(char **str);
int		ft_isspace(char c);
int		ft_is_good_quote(char *line);
int		ft_intlen(int n);
void	*ft_realloc_double_array(void *ptr, size_t original_size,
			size_t new_size);
char	*join_strs(char **args);
int		count_double_str(char **args);
char	*get_path(char **envp);
int		is_valid_identifier(const char *key);
void	open_input_file(char *file_name, t_mini *mini);
void	open_output_file(char *file_name, t_mini *mini, int control);
char	*heredoc_filename(void);
int		ft_heredoc_cmp(char *s1, char *s2);

// ERROR
void	ft_error(t_mini *mini, char *error, char *type, int exit);
void	ft_error_syx(t_mini *mini, char *type, int exit);
void	ft_ctrld_error(char *s1);
void	ft_dputstr_fd(char *s1, char *s2, int fd, int error);
void	ft_error_export(char *args);

// FREE
void	free_double_array(char **str);
void	ft_free_all(t_mini *mini);
void	free_table_aux(t_table_aux *aux);
void	free_table(t_table **table);
void	free_token_list(t_token **token);
void	free_envp(t_envp **envp);
void	free_redir(t_redir *redir);

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
void	add_redir_end(t_table_aux *aux, char *file, int type);
t_redir	*copy_redir_node(t_redir *node);
void	change_redir_node(t_mini *mini, t_redir *node, char *file, int type);

//EXECUTE
int		execute(t_mini *mini);
void	handle_output_append_redirection(char *out_append);
void	handle_output_redirection(char *out_redir);
void	handle_input_redirection(char *in_redir);
void	execute_command(t_table *table_aux, t_mini *mini);
int		ft_individual_builtins(t_table *table_aux, t_mini *mini);
int		ft_non_individual_builtins(t_table *table_aux, t_mini *mini);
void	handle_redirection(t_table *table_aux);
t_redir	*copy_redir_list(t_redir *head);
void	execute_child_process(t_mini *mini, t_table *table_aux);
int		execute_single_command(t_mini *mini, t_table *table_aux);
void	ft_check_if_heredoc(t_mini *mini);
int		ind_built_with_redir(t_table *table_aux, t_mini *mini);

//SIGNALS
void	sig_heredoc(int sig);
void	sig_handler(int sig);
void	exit_capture(t_mini *mini, int status);
void	redir_exit_capture(t_mini *mini, int status, int *first);
void	while_signals(t_mini *mini);

#endif