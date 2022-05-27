/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/24 22:53:23 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_pid(t_data *data, int id);
static int	find_path_and_execve(t_data *data, int id);
static void	ft_execve(t_data *data, int id);

int	executor(t_data *data)
{
	int		id;

	g_status_code = 0;
	signal(SIGINT, handler);
	if (!data->number_of_pipes && is_builtins(data->argve[0][0]))
		return (execute_one_cmd(data));
	id = -1;
	create_executor_parametes(data);
	open_pipes(data);
	while (++id < data->number_of_pipes + 1)
	{
		if (data->exec_flag[id] == VAR_DEFINITION)
			continue ;
		data->pid[id] = fork();
		if (data->pid[id] < 0)
		{
			perror("Minishell: Could not fork proccess: ");
			return (FAILURE);
		}
		if (!data->pid[id])
			execute_pid(data, id);
	}
	main_process_handler(data);
	return (SUCCESS);
}

static int	execute_pid(t_data *data, int id)
{
	int	builtin_flag;
	int	save_fd[2];

	save_std_fds(save_fd);
	close_other_fds(id, data);
	file_descriptor_handler(id, data);
	if (!redirect_filter(data, id, save_fd))
	{
		exec_signals();
		builtin_flag = is_builtins(data->argve[id][0]);
		if (builtin_flag)
			builtin_exec(data, builtin_flag, id);
		else
			ft_execve(data, id);
	}
	exit(SUCCESS);
}

static void	ft_execve(t_data *data, int id)
{
	if (ft_strchr(data->argve[id][0], '/'))
	{
		execve(data->argve[id][0], data->argve[id], data->envp);
		printf("Minishell: %s: No such file or directory\n", \
			data->argve[id][0]);
	}
	else
	{
		find_path_and_execve(data, id);
		printf("Minishell: %s: Command not found\n", data->argve[id][0]);
	}
	g_status_code = 127;
	exit(127);
}

static int	find_path_and_execve(t_data *data, int id)
{
	int		i;
	char	*path_aux;

	i = 0;
	path_aux = NULL;
	if (!data->command_path)
		return (FAILURE);
	while (data->command_path[i])
	{
		path_aux = ft_strjoin(data->command_path[i], data->argve[id][0]);
		if (execve(path_aux, data->argve[id], data->envp) < 0)
		{
			if (path_aux)
			{
				free(path_aux);
				path_aux = NULL;
			}
			i++;
		}
	}
	return (FAILURE);
}

void	builtin_exec(t_data *data, int code, int id)
{
	if (code == EXIT)
		mini_exit(data, id);
	else if (code == CD)
		cd(data, id);
	else if (code == ECHO)
		echo(data, id);
	else if (code == PWD)
		pwd();
	else if (code == ENV)
		env(data);
	else if (code == UNSET)
		unset(data, id);
	else if (code == EXPORT)
		export(data, id);
}
