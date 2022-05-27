/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/24 21:20:26 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_process_handler(t_data *data)
{
	int	count;
	int	status;

	count = 0;
	while (count < data->number_of_pipes)
	{
		close(data->fd[count][0]);
		close(data->fd[count][1]);
		count++;
	}
	count = 0;
	while (count < data->number_of_pipes + 1)
	{
		waitpid(data->pid[count++], &status, 0);
		if (!g_status_code)
			g_status_code = WEXITSTATUS(status);
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
