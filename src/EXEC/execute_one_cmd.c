/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:05:19 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/02 19:59:20 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	restore_std_fds(int *fd);
void	save_std_fds(int *fd);

int	execute_one_cmd(t_data *data)
{
	int		save_fd[2];
	int		builtin;

	builtin = is_builtins(data->argve[0][0]);
	save_std_fds(save_fd);
	redirect_filter(data, 0);
	builtin_exec(data, builtin, 0);
	restore_std_fds(save_fd);
	return (SUCCESS);
}

void	restore_std_fds(int *fd)
{
	dup2(fd[STDOUT], STDOUT_FILENO);
	close(fd[STDOUT]);
	dup2(fd[STDIN], STDIN_FILENO);
	close(fd[STDIN]);
}

void	save_std_fds(int *fd)
{
	fd[STDIN] = dup(STDIN_FILENO);
	fd[STDOUT] = dup(STDOUT_FILENO);
}
