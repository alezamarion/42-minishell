/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:26:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/02 23:54:47 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	redirect(char *file, int flags, int std_fd);

int	redirect_filter(t_data *data, int id)
{
	int	i;
	int	status;

	if (!data->file[id])
		return (SUCCESS);
	status = 0;
	i = 0;
	while (data->file_mode[id][i])
	{
		if (data->file_mode[id][i] == GREAT)
			status += redirect(data->file[id][i], O_WRONLY | O_CREAT | O_TRUNC, STDOUT);
		else if (data->file_mode[id][i] == GREATGREAT)
			status += redirect(data->file[id][i], O_WRONLY | O_CREAT | O_APPEND, STDOUT);
		else if (data->file_mode[id][i] == LESS)
			status += redirect(data->file[id][i], O_RDONLY, STDIN);
		else if (data->file_mode[id][i] == LESSLESS)
			if (heredoc(data->file[id][i]))
				return (FAILURE);
		i++;
	}
	return (status);
}

static int	redirect(char *file, int flags, int std_fd)
{
	int	fd;

	if (!std_fd)
		fd = open(file, flags);
	else
		fd = open(file, flags, 0777);
	if (fd == -1)
		perror("Minishell: Open function failed:");
	else
	{
		dup2(fd, std_fd);
		close(fd);
		return (SUCCESS);
	}
	return (FAILURE);
}
