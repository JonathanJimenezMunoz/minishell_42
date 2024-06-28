/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:24:01 by david             #+#    #+#             */
/*   Updated: 2024/06/28 23:44:21 by david            ###   ########.fr       */
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
	struct s_token		*prev;
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
} t_mini;

// TOKEN_MAIN.C
int tokenize_line(char *line, t_mini *mini);

// TOKEN_DLL.C
t_token	*token_new(char *content, int type);
void	token_add_back(t_token **tokens, t_token *new);
void	token_print(t_token *tokens);
int		ft_add_token(t_token_type type, char **line, t_mini *mini, int size);


// FT_UTILS1.C
void 	ft_clear_spaces(char **line);
int 	ft_isspace(char c);
int 	ft_is_good_quote(char *line);
void	ft_error(t_mini *mini, char *error);
void ft_error_aux(t_mini *mini, t_table_aux *aux, char *error);

// FREE_HANDLER.C
void free_token_list(t_token **token);
void free_table(t_table **table);
void free_table_aux(t_table_aux *aux);

// PARSER_MAIN.C
int parser_token(t_mini *mini);

// PARSER_SLL.C
t_table *create_node(t_table_aux *aux);
int add_node(t_mini **head, t_table_aux *aux);
#endif