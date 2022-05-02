/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fds_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/23 13:07:57 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_pipes(t_data *data)
{
	int	id;
	int	j;

	id = 0;
	while (id < data->number_of_pipes) //open pipes
	{
		if ((pipe(data->fd[id++])) < 0)
		{
			perror("pipe");
			j = 0;
			while (j < id)
			{
				close(data->fd[j][0]);
				close(data->fd[j][1]);
				j++;
			}
			exit (FAILURE); //tratar?
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
		j++;
	}
	j = 0;
	while (j < data->number_of_pipes)
	{
		if (j != id - 1)
			close(data->fd[j][0]);
		j++;
	}
	return (SUCCESS); //tratar erros
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
	return (SUCCESS); //tratar erros(dup)?
}

int	file_descriptor_handler(int id, t_data *data)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
	if (id == 0) //FIRST_CMD
		fd_in = NOT_EXIST;
	if (id == data->number_of_pipes) //LAST_CMD
		fd_out = NOT_EXIST;
	if (fd_in != NOT_EXIST)
		fd_in = data->fd[id - 1][0];
	if (fd_out != NOT_EXIST)
		fd_out = data->fd[id][1];
	stdin_stdout_handler(fd_in, fd_out);
	return (SUCCESS); //tratar erros
}

int	scope_fd_select(int id, t_data *data) //t_data *data, 
{
	// int data->number_of_pipes, int fd[n_pipes][2]
	close_other_fds(id, data);
	file_descriptor_handler(id, data);
	return (SUCCESS); //tratar erros
}
