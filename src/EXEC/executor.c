/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/25 23:43:59 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execve(t_data *data, int argve_index)
{
	int		i;

	data->path_aux = NULL;
	i = 0;
	while (data->command_path[i])
	{
		data->path_aux = ft_strjoin(data->command_path[i], \
			data->argve[argve_index][0]);
		if (execve(data->path_aux, data->argve[argve_index], data->envp) < 0)
		{
			if (data->path_aux)
			{
				free(data->path_aux);
				data->path_aux = NULL;
			}
			i++;
		}
	}
	printf("Minishell: command not found: %s\n", data->argve[argve_index][0]);
}

void	builtin_exec(t_data *data, int code)
{
	if (code == EXIT)
		mini_exit(data);
	else if (code == CD)
		chdir(data->argve[0][1]);
	else if (code == ECHO)
		echo(data);
	else if (code == HELLO)
		hello();
	else if (code == HELP)
		open_help();
	else if (code == PWD)
		pwd();
	else if (code == ENV)
	 	env(data);
}

int	execute_pid(t_data *data, int id)
{
	int	builtin_flag;

	exec_signals();
	redirect_filter(data, id);
	builtin_flag = is_builtins(data->argve[id][0]);
	if (builtin_flag)
	{
		builtin_exec(data, builtin_flag);
		exit (SUCCESS);
	}
	else
	{
		ft_execve(data, id);
		exit (FAILURE);
	}
}

void	create_executor_parametes(t_data *data)
{
	int		i;

	i = 0;
	data->pid = (int *)ft_calloc(sizeof(int), data->number_of_pipes + 1);
	data->fd = (int **)ft_calloc(sizeof(int *), data->number_of_pipes + 1);
	if (!data->pid || !data->fd)
		exit_minishell(data, FAILURE);
	while (i < data->number_of_pipes)
	{
		data->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->fd[i])
			exit_minishell(data, FAILURE);
		i++;
	}
}

int	executor(t_data *data)
{
	int		id;

	check_exit(data);
	create_executor_parametes(data);
	open_pipes(data);
	id = 0;
	if (data->exec_flag == -1)
		return SUCCESS;
	while (id < data->number_of_pipes + 1)
	{
		data->pid[id] = fork();
		if (data->pid[id] < 0)
		{
			perror("Fork");
			return (FAILURE);
		}
		if (data->pid[id] == 0)
		{	
			scope_fd_select(id, data);
			execute_pid(data, id);
			return (SUCCESS);
		}
		if (data->path_aux)
			free(data->path_aux);
		id++;
	}
	main_process_handler(data);
	return (SUCCESS); //tratar erros
}
