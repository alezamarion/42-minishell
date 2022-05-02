/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:16:34 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/25 02:59:10 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtins(char *cmd)
{
	int		i;
	int		switcher;
	char	*builtin_cmd[NUMBER_OF_BUILTINS];

	i = 0;
	switcher = 0;
	builtin_cmd[0] = "exit";
	builtin_cmd[1] = "cd";
	builtin_cmd[2] = "echo";
	builtin_cmd[3] = "hello";
	builtin_cmd[4] = "help";
	builtin_cmd[5] = "pwd";
	builtin_cmd[6] = "env";
	while (i < NUMBER_OF_BUILTINS)
	{
		if (strcmp(cmd, builtin_cmd[i]) == 0)
		{
			switcher = i + 1;
			break ;
		}
		i++;
	}
	if (switcher)
		return (switcher);
	return (FALSE);
}
