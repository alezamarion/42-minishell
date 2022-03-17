/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/16 23:56:42 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function for finding pipe
int parse_pipe(char *str, char **strpiped)
{
	strpiped = ft_split(str, '|');
	if (strpiped[1] == NULL)
		return (0);
	else
		return (1);
}

// function for parsing command words
void parse_space(char *str, char **parsed)
{
	int i;

	i = 0;

	parsed = ft_split(str, ' ');

	// print variable
	while (parsed[i])
	{
		printf("......................PARSED: %s\n", parsed[i]);
		i++;
	}
}

int process_string(char *str, char **parsed, char **parsedpipe)
{
	char *strpiped[2];
	int piped;

	piped = 0;
	piped = parse_pipe(str, strpiped);
	if (piped)
	{
		parse_space(strpiped[0], parsed);
		parse_space(strpiped[1], parsedpipe);
	}
	else
		parse_space(str, parsed);
	if (own_cmd_handler(&str))
	{
		printf("                                      BUILTIN (yes)\n");
		return (SUCESS);
	}
	else
	{
		printf("                                      BUILTIN (no)");
		return (1 + piped);
	}
}
