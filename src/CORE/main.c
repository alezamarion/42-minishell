/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/05/10 10:42:37 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_code = 0;

void	welcome(void)
{
	char	*username;

	printf("\033[H\033[J");
	username = getenv("USER");
	printf("\e[32m*******************************************\e[39m\n");
	printf("\e[32m|                                         |\e[39m\n");
	printf("\e[32m|             MINISHELL  v1.0             |\e[39m\n");
	printf("\e[32m|                                         |\e[39m\n");
	printf("\e[32m*******************************************\e[39m\n");
	printf("\n\n\n\e[32mHi, @%s!\e[39m\n\n", username);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc > 1 && *argv)
	{
		ft_putendl_fd("Minishell: Too many arguments", 2);
		return (FAILURE);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		perror("Minishell: [data] Malloc error");
		return (FAILURE);
	}
	welcome();
	init_data(data, envp);
	while (TRUE)
		minishell(data);
	return (0);
}
