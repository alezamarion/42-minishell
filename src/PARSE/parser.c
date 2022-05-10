/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by joeduard          #+#    #+#             */
/*   Updated: 2022/05/02 23:03:19 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// functions for parsing command line
void	parser(t_data *data)
{
	int	i;

	i = 0;
	while (data->argve[0][i])
		grab_vars(data, data->argve[0][i++]);
	if (is_builtins(data->argve[0][0]) == EXPORT)
		data->exec_flag = 1;
}
