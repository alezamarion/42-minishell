/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:09:01 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/10 10:44:10 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_on_history(char *buf, char *old_input)
{
	if (!old_input || ft_strcmp(old_input, buf))
		add_history(buf);
}
