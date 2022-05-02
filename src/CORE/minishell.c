/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:28:30 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/23 13:28:35 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	minishell(t_data *data)
{
	signal(SIGINT, new_prompt_mini); //Ctrl C
	signal(SIGTERM, SIG_IGN); //Ctrl D --SIGQUIT?
	data_clean(data);
	if (take_input(data))
		return ;//captura na estrutura data->input
	lexer(data); //analise lexica - tokens - apenas divisao
	parser(data); //analise sintatica - quotes, etc
	expander(data); //final do processo - alias
	executor(data); //triagem e execução
}
