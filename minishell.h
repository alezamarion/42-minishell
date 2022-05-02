/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:10:08 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/25 23:43:39 by ocarlos-         ###   ########.fr       */
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
#include <signal.h>

#define NO_PIPE		0

#define NUMBER_OF_BUILTINS 7

#define EXIT		1
#define CD			2
#define ECHO		3
#define HELLO		4
#define HELP		5
#define PWD			6
#define ENV			7
#define	NONE		0

#define SQUOTES 39
#define DQUOTES 34
#define NO_QUOTES_FOUND -1

// CÓDIGO DA MARCE
# define OFF 0
# define ON  1
# define SUCCESS			0
# define FAILURE			1

# define FALSE				0
# define TRUE				1
# define GARBAGE			-1
# define NOT_EXIST			-2

# define GREAT				1
# define GREATGREAT			2
# define LESS				3
# define LESSLESS			6

// Clearing the shell using escape sequences
# define clear() printf("\033[H\033[J")

typedef struct	s_vdt
{
	char	*value;
	int		is_envp;
	int		is_malloc;
}				t_vdt;

typedef struct	s_vars
{
	char			*var_name;
	char			*var_value;
	int				env;
	int				is_malloc;
	struct s_vars	*next;
}				t_vars;

typedef struct s_data
{
	char	*username;
	char	**envp;
	char	**command_path;
	char	*path_aux;
	char	*input;
	char	*old_input;
	char	**cmds_piped;
	char	***argve;
	t_vars	*vars;
	int		number_of_pipes;
	int		**fd;
	int		*pid;
	int		exec_flag;
	int		exit_flag;
	char	***file;
	char	**file_mode;
	char	**tokens;
	char	*string;
}				t_data;

//..................................................CORE
//data_handler.c
void	init_data(t_data *data, char **envp);
int		init_command_path(t_data *data);
void	data_clean(t_data *data);
void	double_free(void ***ptr);
void	triple_free(char ****ptr, int number_of_ids);

//signals.c
void	handler(int signal);
void	exec_signals(void);
void	new_prompt_mini(int signal);

//minishell.c
void	minishell(t_data *data);
char	*handle_quotes(char *str);
int		find_quote(char *str);
void	single_quotes(char *from_single_quotes, char *str);
void	double_quotes(char *from_double_quotes, char *str);

//..................................................PROMPT
//prompt_take_input.c
int		take_input(t_data *data);
void	prompt(t_data *data);

void	print_dir(void);

//history.c
void	put_on_history(char *buf, char *old_input);

//..................................................LEX
//lexer.c - tokens
void	lexer(t_data *data);
void	pull_pipe(t_data *data);
void	pull_space(t_data *data);

//---------LEXER------------//
void	treat_input(t_data *data);
void	treat_input_chars(t_data *data);
void	treat_char(t_data *data, char c, int number);

void	treat_token_strings(t_data *data);
void	treat_quotes(char *token);
void	no_quotes(char *token);
void	reverse_char(char *cmd, int nbr, char c);

char	*reverse_quotes_treat(char *str);
char	*tokens_to_string(char const *s1, char const *s2);
void	fill_redirects(t_data *data);

//..................................................PARSE
//parser.c  -  quotes ok: analisa!
void	parser(t_data *data);

//parse_vars.c
char	*get_var_value(char *input);
char	*get_var_name(char *input);
void	update_envp(t_data *data, char* name, char* value, t_vdt vdt);
void	grab_vars(t_data *data, char *str);

//..................................................EXPANDER
//expand_variables.c
void	expander(t_data *data);

//..................................................EXEC
//sorting.c
int		is_builtins(char *cmd);

//redirects.c
void	new_prompt_heredoc(int signal);
void	redirect(char *file, int flags, int std_fd);
void	heredoc(char *eof);
void	redirect_filter(t_data *data, int id);

//executor.c
int		executor(t_data *data);
int		execute_pid(t_data *data, int id);
void	ft_execve(t_data *data, int argve_index);
int		multiple_exec(t_data *data);
void	builtin_exec(t_data *data, int code);
int		env(t_data *data);

//pipes_fds_handling.c 
int		open_pipes(t_data *data);
int		close_other_fds(int id, t_data *data);
int		stdin_stdout_handler(int in, int out);
int		file_descriptor_handler(int id, t_data *data);
int		scope_fd_select(int id, t_data *data);
int		redir_execute_pid(t_data *data, int id);

//processes_handler.c
void	main_process_handler(t_data *data);

//..................................................BUILTINS
//exit.c
int		exit_minishell(t_data *data, int status);
void	check_exit(t_data *data);
void	mini_exit(t_data *data);

//pwd.c
void	pwd(void);

//help.c
void	open_help(void);

//echo.c
void	echo(t_data *data);

//hello.c
void	hello(void);

//..................................................TOOLS
// Vamos usar funcoes proprias
//str_tools.c
int		ft_strcpy_handled(char **new, char const *src);
int		ft_strjoin_handled(char **s1, char const *s2);
int		ft_str_count(char **str);
void	ft_strcut(char **str, size_t init, size_t end);

//list_tools.c
t_vars	*new_node(char *name, char *value);
t_vars	*last_in_list(t_vars *lst);
void	add_to_list(t_vars **lst, char *name, char *value);
void	clear_list(t_vars *lst);
t_vdt	find_in_list(char *var_name, t_vars *lst);
void	change_in_list(t_vars *lst, char *var_name, char *var_value);
int		is_envp(char *name, t_vars *lst);

//////////////////////////////////////////////////////////

#endif
