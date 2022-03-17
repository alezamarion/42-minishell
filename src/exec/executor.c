/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/16 23:50:57 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function where the system command is executed
void	exec_args(char **parsed)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return ;
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command..");
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		return ;
	}
}

// Function where the piped system commands is executed
void	exec_args_piped(char **parsed, char **parsedpipe)
{
	int		pipefd[2];
	pid_t	p1;
	pid_t	p2;

	if (pipe(pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return ;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("\nCould not fork");
		return ;
	}
	if (p1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command 1..");
			exit(0);
		}
	}
	else
	{
		p2 = fork();
		if (p2 < 0)
		{
			printf("\nCould not fork");
			return ;
		}
		if (p2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(parsedpipe[0], parsedpipe) < 0)
			{
				printf("\nCould not execute command 2..");
				exit(0);
			}
		}
		else
		{
			wait(NULL);
			wait(NULL);
		}
	}
}

// Help command builtin
void	open_help(void)
{
	puts("\n***WELCOME TO MY SHELL HELP***"
		"\nCopyright @ Suprotik Dey"
		"\n-Use the shell at your own risk..."
		"\nList of Commands supported:"
		"\n>cd"
		"\n>ls"
		"\n>exit"
		"\n>all other general commands available in UNIX shell"
		"\n>pipe handling"
		"\n>improper space handling");
	return ;
}

// Function to execute builtin commands
int	own_cmd_handler(char **parsed)
{
	int		i;
	int		switch_own_arg;
	char	*list_of_own_cmds[4];
	char	*username;

	i = 0;
	switch_own_arg = 0;
	list_of_own_cmds[0] = "exit";
	list_of_own_cmds[1] = "cd";
	list_of_own_cmds[2] = "help";
	list_of_own_cmds[3] = "hello";
	while (i < 4)
	{
		if (strcmp(parsed[0], list_of_own_cmds[i]) == 0)
		{
			switch_own_arg = i + 1;
			break ;
		}
		i++;
	}
	if (switch_own_arg == 1)
	{
		printf("\nGoodbye\n");
		exit(0);
	}
	else if (switch_own_arg == 2)
	{
		chdir(parsed[1]);
		return (1);
	}
	else if (switch_own_arg == 3)
	{
		open_help();
		return (1);
	}
	else if (switch_own_arg == 4)
	{
		username = getenv("USER");
		printf("\nHello %s.\nMind that this is not a place to play around."
			"\nUse help to know more..\n", username);
		return (1);
	}
	return (0);
}
