/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/15 17:01:04 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** execflag returns zero if there is no command
		// or it is a builtin command,
		// 1 if it is a simple command
		// 2 if it is including a pipe.
*/
#include "../minishell.h"

char **g_envp;

// void	init_shell(void)
// {
// 	char	*username;

// 	clear();
// 	printf("\n\n******************");
// 	printf("\n\t****MY SHELL****");
// 	printf("\n\n*******************");
// 	username = getenv("USER");
// 	printf("\n\n\nUSER is: @%s\n", username);
// 	sleep(2);
// 	clear();
// }

void init_data(t_data **data)
{
	t_data *node;

	node = (t_data *)malloc(sizeof(t_data));
	node->exec_flag = 0;
	*data = node;
//	free(node);
}

int	main(int argc, char **argv, char **envp)
{
	t_data *data;

	(void)argc;
	(void)argv;
	g_envp = envp;
//	init_shell();
	init_data(&data);
	while (1)
		minishell(data);
	return (0);
}
