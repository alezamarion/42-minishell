/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:27:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/23 13:31:08 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_minishell(t_data *data, int status)
{	
	data_clean(data);
	if (data->old_input)
		free(data->old_input);
	double_free((void ***)&data->command_path);
	rl_clear_history();
	free(data);
	exit (status);
}

void	check_exit(t_data *data)
{
	int	builtin_flag;

	if (data->number_of_pipes == 0)
	{
		builtin_flag = is_builtins(data->argve[0][0]);
		if (builtin_flag == EXIT)
			mini_exit(data);
	}
}

void	mini_exit(t_data *data)
{
	if (data->number_of_pipes == 0)
	{
		data->exit_flag = TRUE; //Setada apenas no pai (single exec)
		printf("\nGoodbye!\n");
		exit_minishell(data, SUCCESS);
	}	
}
