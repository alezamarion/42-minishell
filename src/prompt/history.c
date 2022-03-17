/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:09:01 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/17 00:05:15 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void put_on_history(char *buf, char *old_input)
{	
	if (!old_input || ft_strcmp(old_input, buf)) //N repete hist
		add_history(buf); 
}