/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:24:01 by david             #+#    #+#             */
/*   Updated: 2024/07/12 23:07:30 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <termios.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"


typedef enum e_token_type
{
	TOKEN_WORD,// char, number ...
	TOKEN_PIPE,// |
	TOKEN_REDIR_IN,// <
	TOKEN_REDIR_OUT,// >
	TOKEN_REDIR_APPEND,// >>
	TOKEN_REDIR_DELIMITER,// <<
	// Podria faltar "" '' () $ $?
} t_token_type;

typedef struct s_token
{
	char				*content;
	t_token_type		type;
	struct s_token		*next;
} t_token;

typedef struct s_envp
{
	char	*key;
	char	*value;
	struct s_envp	*next;
} t_envp;

typedef struct s_table
{
	char	*cmd;
	char	*args;
	char	*in_redir;
	char	*out_redir;
	char	*in_heredoc;
	char 	*out_append;	
	struct s_table	*next;
} t_table;

typedef struct s_table_aux
{
	char	*cmd;
	char	*args;
	char	*in_redir;
	char	*out_redir;
	char	*in_heredoc;
	char 	*out_append;
} t_table_aux;

typedef struct s_mini
{
	t_token	*tokens;
	t_table	*table;
	int 	error;
	t_envp	*envp;
} t_mini;

// TOKEN_MAIN.C
int tokenize_line(char *line, t_mini *mini);

// TOKEN_LIST.C
t_token	*token_new(char *content, t_token_type type);
void	token_print(t_token *tokens);
int		ft_add_token(t_token_type type, char **line, t_mini *mini, int size);

// FT_UTILS1.C
void 	ft_clear_spaces(char **line);
int 	ft_isspace(char c);
int 	ft_is_good_quote(char *line);
void ft_error(t_mini *mini, char *error, char *type);
void ft_error_aux(t_mini *mini, t_table_aux *aux, char *error, char *type);

// FREE_HANDLER.C
void free_token_list(t_token **token);
void free_table(t_table **table);
void free_table_aux(t_table_aux *aux);
void free_envp(t_envp **envp);
void	ft_free_all(t_mini *mini);

// PARSER_MAIN.C
int parser_token(t_mini *mini);

// PARSER_LIST.C
t_table *create_node(t_table_aux *aux);
int add_node(t_mini **head, t_table_aux *aux);
void print_table(t_table *table);

// PARSER_HANDLER.C
void parse_cmd_args(t_table_aux *aux, int *first_word, t_token **current);
void parse_redir_in(t_mini *mini, t_table_aux *aux, t_token **current);
void parser_redir_out(t_mini *mini, t_table_aux *aux, t_token **current);
void parse_redir_append(t_mini *mini, t_table_aux *aux, t_token **current);
void parse_redir_heredoc(t_mini *mini, t_table_aux *aux, t_token **current);


// ENVP_LIST.C
void envp_init(t_envp **envp, char **envp_list);
void	add_node_to_envp(t_envp **envp, t_envp *new_node);
char	*envp_get_value(t_envp *envp, char *key);
void envp_print(t_envp *envp);

// BUILTINS
int ft_pwd(void);
int ft_echo(char *args);
void ft_envp(t_envp *envp);
int ft_export(char *args, t_envp **envp);
void	ft_exit(char *str_arg, t_mini *mini);
int		ft_cd(char *args, t_envp *envp);
void	ft_unset(char *key, t_mini *mini);


#endif