/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:18:13 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/12 22:36:47 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TMP_FILE	"/tmp/minishell_here_document"
#define NO_DELIMITER "minishell: warning: here-document at \
line %d delimited by end-of-file (wanted `%s')\n"

static int	create_tmp_file(void);
static void	redirect_tmp_file_input(void);
static void	clear_tmp_file(void);
static void	write_input(char *eof, int tmp_file);

int	heredoc(char *eof, int *save_fd)
{
	int		tmp_file;
	int		status;
	int		save_std_out;

	tmp_file = create_tmp_file();
	if (tmp_file < 0)
		return (FAILURE);
	save_std_out = dup(STDOUT);
	dup2(save_fd[STDOUT], STDOUT_FILENO);
	dup2(save_fd[STDIN], STDIN_FILENO);
	signal(SIGINT, SIG_IGN);
	if (!fork())
		write_input(eof, tmp_file);
	wait(&status);
	if (WEXITSTATUS(status) == 130)
	{
		clear_tmp_file();
		g_status_code = 130;
		return (FAILURE);
	}
	redirect_tmp_file_input();
	dup2(save_std_out, STDOUT_FILENO);
	close(save_std_out);
	return (SUCCESS);
}

static int	create_tmp_file(void)
{
	int	fd;

	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		perror("Minishell: Could not create temp file: %s");
	return (fd);
}

static void	redirect_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_RDONLY);
	dup2(tmp_fd, STDIN);
	close(tmp_fd);
	unlink(TMP_FILE);
}

static void	clear_tmp_file(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
	close(tmp_fd);
}

static void	write_input(char *eof, int tmp_file)
{
	char	*input;
	int		line;

	line = 0;
	signal(SIGINT, interrupt_input_writing);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			ft_printf(STDERR, NO_DELIMITER, line, eof);
			close(tmp_file);
			exit(0);
		}
		if (!ft_strcmp(input, eof))
		{
			free(input);
			close(tmp_file);
			exit(0);
		}
		ft_putendl_fd(input, tmp_file);
		free(input);
		line++;
	}
}
