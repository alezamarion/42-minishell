/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:52:40 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/10 20:39:32 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Creates a new prompt.
*/
void	new_prompt_mini(int signal)
{
	(void)signal;
	g_status_code = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
	Handling signals for child process.
*/
void	handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_status_code = 130;
	}
	else
	{
		printf("Quit (core dumped)\n");
		g_status_code = 131;
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
