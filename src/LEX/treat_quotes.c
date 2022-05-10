/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:55:15 by azamario          #+#    #+#             */
/*   Updated: 2022/05/02 22:25:19 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Mascara todos os caracteres de sintaxe e espaços entre aspas,
	divide o input em tokens
	(o que estiver entre aspas é um token) e remove as aspas deles.
	Por fim converte os tokens em uma nova string de input.
*/
int	pull_quotes(t_data *data)
{
	if (mask_all_chars(data))
		return (FAILURE);
	data->tokens = ft_split(data->input, ' ');
	treat_token_strings(data);
	return (SUCCESS);
}

/*
	Trata os tokens e os juntam devolta na string de input.
*/
void	treat_token_strings(t_data *data)
{
	char	*buf;
	char	*string;
	int		i;

	i = 0;
	string = NULL;
	while (data->tokens[i])
	{
		treat_quotes(data->tokens[i]);
		no_quotes(data->tokens[i]);
		if (!string)
			string = tokens_to_string(string, data->tokens[i]);
		else
		{
			buf = tokens_to_string(string, data->tokens[i]);
			free(string);
			string = ft_strdup(buf);
			free(buf);
		}
		i++;
	}
	free(data->input);
	data->input = ft_strdup(string);
	free(string);
}

/*
	Substitui as aspas internas por 2 ou 3.
	E.g
	echo\0 "'jorge'1ale"\0.
	echo\0 "3jorge31ale"\0.
*/
void	treat_quotes(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			while (token[++i] != '\'')
			{
				if (token[i] == '\"')
					token[i] = 2;
			}
		}
		if (token[i] == '\"')
		{
			while (token[++i] != '\"')
			{
				if (token[i] == '\'')
					token[i] = 3;
			}
		}
		i++;
	}
}

/*
	Retira as aspas "3jorge31ale"\0 e depois reverte aspas escondidas: 'jorge'1ale\0
*/
void	no_quotes(char *token)
{
	int		quotes;
	char	*string;
	int		i;
	int		j;

	quotes = 0;
	i = -1;
	while (token[++i])
		if (token[i] == '\'' || token[i] == '\"')
			quotes++;
	if (!quotes)
		return ;
	string = ft_calloc((ft_strlen(token) - quotes + 1), sizeof(char));
	i = -1;
	j = 0;
	while (token[++i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			continue ;
		string[j++] = token[i];
	}
	string = reverse_quotes_treat(string);
	ft_strlcpy(token, string, ft_strlen(string) + 1);
	free(string);
}

char	*tokens_to_string(char const *s1, char const *s2)
{
	char		*string;
	int			space;
	size_t		i;
	size_t		j;

	i = 0;
	space = ft_strlen(s1) != 0;
	string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1 + space) * sizeof(char));
	if (!string)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			string[i] = s1[i];
			i++;
		}
		string[i++] = ' ';
	}
	j = -1;
	while (s2[++j])
		string[i + j] = s2[j];
	string[i + j] = '\0';
	return (string);
}
