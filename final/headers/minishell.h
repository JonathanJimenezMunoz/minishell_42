/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:50:07 by david             #+#    #+#             */
/*   Updated: 2024/08/31 18:15:49 by david            ###   ########.fr       */
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

typedef struct s_table
{
	char			**args;
	char			**in_redir;
	char			**out_redir;
	char			**in_heredoc;
	char			**out_append;	
	struct s_table	*next;
}	t_table;

typedef struct s_table_aux
{
	char	**args;
	char	**in_redir;
	char	**out_redir;
	char	**in_heredoc;
	char	**out_append;
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
}	t_mini;

// ENVP
void	envp_init(t_envp **envp, char **envp_list);
char	*envp_get_value(t_envp *envp, char *key);
void	envp_print(t_envp *envp);
void	add_node_to_envp(t_envp **envp, t_envp *new_node);

// UTILS
char	**copy_double_str(char **str);
int		ft_isspace(char c);
int		ft_is_good_quote(char *line);
int		ft_intlen(int n);
char	**ft_realloc_double_array(char **str, int new_size);

// ERROR
void	ft_error(t_mini *mini, char *error, char *type, int exit);

// FREE
void	free_double_array(char **str);
void	ft_free_all(t_mini *mini);
void	free_table_aux(t_table_aux *aux);

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

//SIGNALS
void	sig_heredoc(int sig);
void	exit_capture_heredoc(t_mini *mini, int status);

// TEMPORALES
void	token_print(t_token *tokens);

# endif