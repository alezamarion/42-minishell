/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:29:32 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/12 00:29:33 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_clean(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->pid)
		free(data->pid);
	data->input = NULL;
	data->pid = NULL;
	double_free((void ***)&data->fd);
	double_free((void ***)&data->cmds_piped);
	double_free((void ***)&data->file_mode);
	triple_free(&data->file, data->number_of_pipes + 1);
	triple_free(&data->argve, data->number_of_pipes + 1);
	data->number_of_pipes = GARBAGE;
	if (data->exec_flag)
		free(data->exec_flag);
	data->exec_flag = NULL;
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
