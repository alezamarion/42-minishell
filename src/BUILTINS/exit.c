/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:27:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/02 22:57:16 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_minishell(t_data *data, int status)
{	
	data_clean(data);
	if (data->old_input)
		free(data->old_input);
	double_free((void ***)&data->command_path);
	double_free((void ***)&data->envp);
	clear_list(data->vars);
	rl_clear_history();
	free(data);
	exit(status);
}

void	mini_exit(t_data *data)
{
	printf("\nGoodbye!\n");
	exit_minishell(data, SUCCESS);
}
