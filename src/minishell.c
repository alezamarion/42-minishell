/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/11 19:57:35 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell(t_data *data)
{
	print_dir();
		if (take_input(data->input_string))
	//		continue ;
		printf("INPUT %s\n", data->input_string);
		data->exec_flag = process_string(data->input_string, data->parsed_args,
				data->parsed_args_piped);
		if (data->exec_flag == 1)
			exec_args(data->parsed_args);
		if (data->exec_flag == 2)
			exec_args_piped(data->parsed_args, data->parsed_args_piped);
}


