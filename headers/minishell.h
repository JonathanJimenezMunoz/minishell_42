/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:24:01 by david             #+#    #+#             */
/*   Updated: 2024/06/25 23:53:22 by david            ###   ########.fr       */
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

typedef struct s_token
{
	char	*content;
	int		type;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

typedef struct s_envp
{
	char	*key;
	char	*value;
	struct s_envp	*next;
} t_envp;

typedef struct s_mini
{
	t_token	*tokens;
} t_mini;

// TOKEN_MAIN.C
int tokenize_line(char **line, t_mini **mini);
#endif