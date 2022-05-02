/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/23 14:43:17 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	main_process_handler(t_data *data)
{
	int	count;

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
		waitpid(data->pid[count], NULL, 0);
		count++;
	}
}
