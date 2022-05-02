/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:20 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/26 00:04:15 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data(t_data *data, char **envp)
{	
	ft_bzero(data, sizeof(t_data));
	data->envp = envp;
	init_command_path(data);
	data->number_of_pipes = GARBAGE;
	data->exec_flag = GARBAGE;
}

int	init_command_path(t_data *data)
{
	int i;
	int ret;
	t_vars	*temp;

	data->command_path = ft_split(getenv("PATH"), ':');
	
	i = 0;
	while (data->command_path[i] != NULL)
	{
		ret = ft_strjoin_handled(&(data->command_path[i]), "/");
		if (ret == FAILURE)
		{
			printf("Init failed\n");
			exit_minishell(data, FAILURE);
		}
		i++;
	}
	i = 0;
	while (data->envp[i])
	{
		grab_vars(data, data->envp[i]);
		temp = last_in_list(data->vars);
		temp->env = i++;
		temp->is_malloc = 0;
	}
	return SUCCESS;
}

void	data_clean(t_data *data)
{
	if (data->string)
	{
		free(data->string);
		data->string = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	double_free((void ***)&data->fd);
	double_free((void ***)&data->cmds_piped);
	double_free((void ***)&data->tokens);
	double_free((void ***)&data->file_mode);
	triple_free(&data->file, data->number_of_pipes + 1);
	triple_free(&data->argve, data->number_of_pipes + 1);
	data->number_of_pipes = GARBAGE;
	data->exec_flag = GARBAGE;
}

void	double_free(void ***ptr)
{
	int		i;

	i = 0;
	if (!*ptr)
		return ;
	while ((*ptr)[i])
	{
		if ((*ptr)[i])
			free((*ptr)[i]);
		(*ptr)[i] = NULL;
		i++;
	}
	free(*ptr);
	*ptr = NULL;
}

void	triple_free(char ****ptr, int number_of_ids)
{
	int		id;
	int		cmd;

	if (!*ptr)
		return ;
	id = 0;
	while (id < number_of_ids)
	{
		if ((*ptr)[id])
		{
			cmd = 0;
			while ((*ptr)[id][cmd])
			{
				if ((*ptr)[id][cmd])
					free((*ptr)[id][cmd]);
				(*ptr)[id][cmd] = NULL;
				cmd++;
			}
			free((*ptr)[id]);
			(*ptr)[id] = NULL;
		}
		id++;
	}
	free(*ptr);
	*ptr = NULL;
}
