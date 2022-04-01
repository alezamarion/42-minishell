/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/31 20:43:11 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** execflag returns zero if there is no command
		// or it is a builtin command,
		// 1 if it is a simple command
		// 2 if it is including a pipe.
*/
#include "../minishell.h"

void	welcome(t_data *data)
{	
	data->username = getenv("USER");
	printf("|			        			|\n");
	printf("|			MINISHELL			|\n");
	printf("|			        			|\n");
	printf("\n\n\nHi, @%s!\n\n", data->username);
	clear();
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	
	(void)argc;
	(void)argv;
	init_data(&data);
	welcome(&data);
	data.envp = envp;
	while (TRUE)
		minishell(&data);
	exit_minishell(&data, SUCCESS);
}
