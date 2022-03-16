/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/15 17:56:05 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// function for parsing command words
void	parse_space(char *str, char **parsed)
{
	int	i;

	i = 0;
	while (i < MAXLIST)
	{
		parsed[i] = strsep(&str, " ");
		if (parsed[i] == NULL)
			break ;
		if (strlen(parsed[i]) == 0)
			i--;
		i++;
	}
}

int	process_string(char *str, char **parsed, char **parsedpipe)
{
	char	*strpiped[2];
	int		piped;

	piped = 0;
	piped = parse_pipe(str, strpiped); // se achar o primeiro argumento do pipe, retorna 0
	if (piped)
	{
		parse_space(strpiped[0], parsed);  // ls -l 
		parse_space(strpiped[1], parsedpipe); // grep documents
	}
//	else
//	{
//		parse_space(str, parsed);
//	}
	if (own_cmd_handler(&str))
	{
		printf("IF\n");
		return (0);
	}
	else
	{
		printf("ELSE");
		return (1 + piped);
	}
}
