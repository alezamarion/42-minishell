/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:26:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/04/23 13:15:56 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define NO_DELIMITER "minishell: warning: here-document at \
		line 13 delimited by end-of-file (wanted `%s')"

void	new_prompt_heredoc(int signal)
{
	write(1, "\n", 1);
	exit(131);
	(void)signal;
}

void	heredoc(char *eof)
{
	char	*input;

	signal(SIGINT, SIG_IGN);
	if (!fork())
	{
		signal(SIGINT, new_prompt_heredoc);
		while (1)
		{
			input = readline("> ");
			if (!input)
			{
				printf(NO_DELIMITER, eof);
				exit(1);
			}
			if (!strcmp(input, eof))
			{
				free(input);
				exit(0);
			}
			ft_putendl_fd(input, 1);
			free(input);
		}
	}
	wait(NULL);
}

void	redirect(char *file, int flags, int std_fd)
{
	int	fd;

	if (!std_fd)
		fd = open(file, flags); //perguntar Vi
	else
		fd = open(file, flags, 0777);
	if (fd == -1)
		perror("Redirect Failed...\n"); //perror("open error");
	else
	{
		dup2(fd, std_fd);
		close(fd);
	}
}

void	redirect_filter(t_data *data, int id)
{
	int	i;

	if (data->file[id])
	{
		i = 0;
		while (data->file_mode[id][i])
		{
			if (data->file_mode[id][i] == GREAT)
				redirect(data->file[id][i], \
					O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
			else if (data->file_mode[id][i] == GREATGREAT)
				redirect(data->file[id][i], \
					O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
			else if (data->file_mode[id][i] == LESS)
				redirect(data->file[id][i], \
					O_RDONLY | O_CREAT, STDIN_FILENO);
			else if (data->file_mode[id][i] == LESSLESS)
				heredoc(data->file[id][i]);
			i++;
		}
	}
}

//:::::pensar em testes eqto terminam parse
// static void _TESTEredir_execute_pid(t_data *data, int id)
// {
//     //Para teste em redir - abre
//     data->file = (char ***)malloc(sizeof(char **) * (1)); //por bloco de pipe
//     (data->file)[id] = (char **)malloc(sizeof(char *) * (3 + 1));
//     printf("Está sendo redirecionado a arquivo! Arquivo criado: ver pasta testes\n");
//     (data->file)[id][0] = "./testes/file_a.txt";// >
//     (data->file)[id][1] = "./testes/file_b_append.txt";//
//     (data->file)[id][2] = "./testes/file_c.txt";//
//     (data->file)[id][3] = NULL; //p usar ft_str_count

//     int file_no = ft_str_count(data->file[id]); 

//     data->file_mode = (int **)malloc(sizeof(int *) * 1);   
//     data->file_mode[id] = (int *)malloc(sizeof(int) * file_no);
//     (data->file_mode)[id][0] = GREAT;
//     (data->file_mode)[id][1] = GREATGREAT;
//     (data->file_mode)[id][2] = GREAT; // 
//     //---para teste fecha
// }
