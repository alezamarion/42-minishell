/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:57:41 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/22 13:17:31 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void hello(void)
{
	char *username;
	
	username = getenv("USER");
	printf("\nHello %s.\nMind that this is not a place to play around."
			"\nUse help to know more..\n", username);
}
