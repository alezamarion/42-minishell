/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:10:08 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/17 00:04:05 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
  
#define MAXCOM		1000 // max number of letters to be supported
#define MAXLIST		100 // max number of commands to be supported
#define MAXPROMPT	100 // max lenght of prompt

#define FAIL		1
#define SUCESS		0
  
#define NO_BUILTINS 4

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

typedef struct	s_data
{
    char	input_string[MAXCOM];
	char	*parsed_args[MAXLIST];
	char	*parsed_args_piped[MAXLIST];
	int		exec_flag;
}				t_data;

//..................................................EXEC
//executor.c
void	exec_args(char** parsed);
void	exec_args_piped(char** parsed, char** parsedpipe);
void	open_help();
int		own_cmd_handler(char** parsed);

//..................................................PARSE
//parser.c
int		parse_pipe(char* str, char** strpiped);
void	parse_space(char* str, char** parsed);
int		process_string(char* str, char** parsed, char** parsedpipe);

//..................................................PROMPT
//history.c
void	put_on_history(char *buf, char *old_input);
//prompt_take_input.c
void	print_dir(void);
int		take_input(char* input);

//..................................................TOOLS
// Vamos usar funcoes proprias


//main.c
void wellcome(void);
void init_shell(t_data *data);








#endif
