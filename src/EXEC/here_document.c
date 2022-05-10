/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:18:13 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/02 22:29:37 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define TMP_FILE	"/tmp/minishell_here_document"
#define NO_DELIMITER "minishell: warning: here-document at \
line %d delimited by end-of-file (wanted `%s')"

static int	create_tmp_file(void);
static void	redirect_tmp_file_input(void);
static void	clear_tmp_file(void);
static void	write_input(char *eof, int tmp_file);

int	heredoc(char *eof)
{
	int		tmp_file;
	int		status;

	signal(SIGINT, SIG_IGN);
	tmp_file = create_tmp_file();
	if (tmp_file < 0)
		return (FAILURE);
	if (!fork())
		write_input(eof, tmp_file);
	wait(&status);
	if (status == 130)
	{
		clear_tmp_file();
		return (FAILURE);
	}
	redirect_tmp_file_input();
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
			exit(0);
		}
		if (!ft_strcmp(input, eof))
		{
			free(input);
			exit(0);
		}
		ft_putendl_fd(input, tmp_file);
		free(input);
		line++;
	}
}
