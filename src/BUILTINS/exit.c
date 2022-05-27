/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:27:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/24 20:32:55 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isdigitstr(char *str);

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
	exit(g_status_code | status);
}

void	mini_exit(t_data *data, int id)
{
	int		args;

	args = ft_str_count(data->argve[id]);
	if (args > 2)
	{
		if (isdigitstr(data->argve[id][1]))
			ft_printf(STDERR, "Minishell: exit: too many arguments\n");
		else
			exit_minishell(data, 2);
	}		
	else
	{
		if (data->number_of_pipes < 1)
			printf("Goodbye!\n");
		if (args == 1)
			exit_minishell(data, 0);
		else if (args == 2)
			exit_minishell(data, ft_atoi(data->argve[id][1]));
	}
	g_status_code = 1;
}

static int	isdigitstr(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
