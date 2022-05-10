/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:10:08 by joeduard          #+#    #+#             */
/*   Updated: 2022/05/04 01:27:02 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ft_printf/inc/ft_printf.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#define NO_PIPE		0

#define NUMBER_OF_BUILTINS 9

#define EXIT		1
#define CD			2
#define ECHO		3
#define HELLO		4
#define HELP		5
#define PWD			6
#define ENV			7
#define EXPORT		8
#define UNSET		9
#define	NONE		0

#define CHAR_MAX_NUM 	1024

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

typedef struct	s_vdt
{
	char	*value;
	int		is_envp;
}				t_vdt;

typedef struct	s_vars
{
	char			*var_name;
	char			*var_value;
	int				env;
	struct s_vars	*next;
}				t_vars;

typedef struct s_data
{
	char	*username;
	char	**envp;
	char	**command_path;
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
	int		child_ret;
	char	***file;
	char	**file_mode;
	char	**tokens;
}				t_data;

//..................................................CORE
//data_handler.c
void	init_data(t_data *data, char **envp);
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
int		lexer(t_data *data);
void	pull_pipe(t_data *data);
void	pull_space(t_data *data);

//---------LEXER------------//
int		pull_quotes(t_data *data);
int		mask_all_chars(t_data *data);
int		mask_character(char *str, char c, int number);

void	treat_token_strings(t_data *data);
void	treat_quotes(char *token);
void	no_quotes(char *token);
void	unmask_character(char *cmd, int nbr, char c);

char	*reverse_quotes_treat(char *str);
char	*tokens_to_string(char const *s1, char const *s2);
int		pull_redirects(t_data *data);

//..................................................PARSE
//parser.c  -  quotes ok: analisa!
void	parser(t_data *data);

//mask_dollar.c
void	mask_dollar(t_data *data);

// mask_n_unmask_chars.c
char	*reverse_quotes_treat(char *str);
void	unmask_character(char *cmd, int nbr, char c);
int		mask_all_chars(t_data *data);
int		mask_character(char *str, char c, int number);

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
void	interrupt_input_writing(int signal);
int		redirect_filter(t_data *data, int id);
int		heredoc(char *eof);

//executor.c
int		executor(t_data *data);
int		execute_pid(t_data *data, int id);
void	ft_execve(t_data *data, int argve_index);
int		multiple_exec(t_data *data);
void	builtin_exec(t_data *data, int code, int id);
int		env(t_data *data);

//pipes_fds_handling.c 
int		open_pipes(t_data *data);
int		close_other_fds(int id, t_data *data);
int		stdin_stdout_handler(int in, int out);
int		file_descriptor_handler(int id, t_data *data);
int		scope_fd_select(int id, t_data *data);
int		redir_execute_pid(t_data *data, int id);

//execute_one_cmd.c
int		execute_one_cmd(t_data *data);

//processes_handler.c
void	main_process_handler(t_data *data);

//..................................................BUILTINS
int 	cd(t_data *data, int id);
void 	pwd();
//exit.c
int		exit_minishell(t_data *data, int status);
void	check_exit(t_data *data);
void	mini_exit(t_data *data);

//pwd.c
void	pwd(void);

//help.c
void	open_help(void);

//echo.c
void	echo(t_data *data, int id);

//hello.c
void	hello(void);

//export.c
void	export(t_data *data, int id);

//unset.c
void	unset(t_data *data, int id);

//..................................................TOOLS
// Vamos usar funcoes proprias
//str_tools.c
int		ft_strcpy_handled(char **new, char const *src);
int		ft_strjoin_handled(char **s1, char const *s2);
int		ft_str_count(char **str);
void	ft_strcut(char **str, size_t init, size_t end);
char	*remount_var(char *var_name, char *var_value);


//list_tools.c
t_vars	*new_node(char *name, char *value);
t_vars	*last_in_list(t_vars *lst);
void	add_to_list(t_vars **lst, char *name, char *value);
void	clear_list(t_vars *lst);
t_vdt	find_in_list(char *var_name, t_vars *lst);
void	change_in_list(t_vars *lst, char *var_name, char *var_value);
int		is_envp(char *name, t_vars *lst);
void	delete_in_list(char *var_name, t_vars **vars);
void	upd_idx_in_list(t_vars *lst, char *var_name, int pos);

//////////////////////////////////////////////////////////

#endif
