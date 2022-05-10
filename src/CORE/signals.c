/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:52:40 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/04 01:15:40 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Creates a new prompt.
*/
void	new_prompt_mini(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

/*
	Handling signals for child process.
*/
void	handler(int signal)
{
	(void)signal;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
	else
	{
		printf("Quit (core dumped)\n");
		exit(131);
	}
}

void	exec_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

void	interrupt_input_writing(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(130);
}
