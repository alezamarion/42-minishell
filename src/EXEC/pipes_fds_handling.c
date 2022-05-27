/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fds_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/10 10:43:02 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(t_data *data)
{
	int	id;
	int	j;

	id = 0;
	while (id < data->number_of_pipes)
	{
		if ((pipe(data->fd[id++])) < 0)
		{
			perror("Minishell: Could not open pipe");
			j = 0;
			while (j < id)
			{
				close(data->fd[j][0]);
				close(data->fd[j][1]);
				j++;
			}
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	close_other_fds(int id, t_data *data)
{
	int	j;

	j = 0;
	while (j < data->number_of_pipes)
	{
		if (j != id)
			close(data->fd[j][1]);
		if (j != id - 1)
			close(data->fd[j][0]);
		j++;
	}
	return (SUCCESS);
}

int	stdin_stdout_handler(int in, int out)
{
	if (in != NOT_EXIST)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != NOT_EXIST)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	return (SUCCESS);
}

int	file_descriptor_handler(int id, t_data *data)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
	if (id == 0)
		fd_in = NOT_EXIST;
	if (id == data->number_of_pipes)
		fd_out = NOT_EXIST;
	if (fd_in != NOT_EXIST)
		fd_in = data->fd[id - 1][0];
	if (fd_out != NOT_EXIST)
		fd_out = data->fd[id][1];
	stdin_stdout_handler(fd_in, fd_out);
	return (SUCCESS);
}
