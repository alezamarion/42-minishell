/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:28:30 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/14 11:45:37 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_data *data)
{
	signal(SIGINT, new_prompt_mini);
	signal(SIGQUIT, SIG_IGN);
	data_clean(data);
	if (take_input(data) || lexer(data))
		return ;
	expander(data);
	if (parser(data))
		return ;
	executor(data);
}
