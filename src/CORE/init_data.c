/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:20 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/22 10:49:44 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	backup_envp_parameter(t_data *data, char **envp);
static void	fill_list_vars(t_data *data);

void	init_data(t_data *data, char **envp)
{	
	ft_bzero(data, sizeof(t_data));
	data->envp = (char **)ft_calloc(ft_str_count(envp) + 1, sizeof(char *));
	if (!data->envp)
		exit_minishell(data, FAILURE);
	backup_envp_parameter(data, envp);
	fill_list_vars(data);
	update_command_path(data);
	data->number_of_pipes = GARBAGE;
	data->exec_flag = NULL;
}

int	update_command_path(t_data *data)
{
	int		i;
	t_vdt	vdt;

	vdt = find_in_list("PATH", data->vars);
	if (data->command_path)
		double_free((void ***)&data->command_path);
	data->command_path = ft_split(vdt.value, ':');
	if (!data->command_path)
	{
		perror("Minishell: [data>command_path] Malloc error");
		return (FAILURE);
	}
	i = 0;
	while (data->command_path[i] != NULL)
	{
		if (ft_strjoin_handled(&(data->command_path[i]), "/") == FAILURE)
		{
			ft_putstr_fd("Init failed\n", 2);
			exit_minishell(data, FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static void	backup_envp_parameter(t_data *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
			exit_minishell(data, FAILURE);
		i++;
	}
}

static void	fill_list_vars(t_data *data)
{
	int		i;
	t_vars	*temp;

	i = 0;
	while (data->envp[i])
	{
		grab_vars(data, data->envp[i]);
		temp = last_in_list(data->vars);
		temp->env = i++;
	}
}
