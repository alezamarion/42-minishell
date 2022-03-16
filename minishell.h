/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:10:08 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/15 16:59:15 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

extern char					**g_envp;
  
#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported
  
// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

#define NO_BUILTINS 4

typedef struct s_data
{
    char	input_string[MAXCOM];
	char	*parsed_args[MAXLIST];
	char	*parsed_args_piped[MAXLIST];
	int		exec_flag;
}t_data;

//init minishell
void init_data(t_data **data);
void init_shell();

void	minishell(t_data *data);

int take_input(char* str);
void print_dir();
void exec_args(char** parsed);
void exec_args_piped(char** parsed, char** parsedpipe);
void open_help();
int own_cmd_handler(char** parsed);
int parse_pipe(char* str, char** strpiped);
void parse_space(char* str, char** parsed);
int process_string(char* str, char** parsed, char** parsedpipe);

#endif
