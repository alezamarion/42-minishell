/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/17 00:01:20 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** execflag returns zero if there is no command
		// or it is a builtin command,
		// 1 if it is a simple command
		// 2 if it is including a pipe.
*/
#include "../minishell.h"

void	wellcome(void)
{
	char	*username;

	clear();
	username = getenv("USER");
	printf("\n\n\nHi, @%s!\n", username);
	clear();
}

void	init_shell(t_data *data)
{
	data->input_string[0] = '\0';
	data->parsed_args[0] = NULL;
	data->parsed_args_piped[0] = NULL;
	data->exec_flag = 0;
}

int	main(void)
{
	t_data data;

	init_shell(&data);
	while (1)
	{
		if (take_input(data.input_string))
			continue ;
		printf(".......................INPUT: %s\n", data.input_string);
		data.exec_flag = process_string(data.input_string, data.parsed_args,
				data.parsed_args_piped);
		if (data.exec_flag == 1)
			exec_args(data.parsed_args);
		if (data.exec_flag == 2)
			exec_args_piped(data.parsed_args, data.parsed_args_piped);
	}
	return (0);
}
