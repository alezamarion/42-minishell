/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:34:34 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/01 17:18:29 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*

int find_quote(char *str)
{
    int i;

    i = 0;
    if (str == 0)
        return (EXIT_FAILURE);
    while (str[i] != '\0')
    {
        if (str[i] == SQUOTES || str[i] == DQUOTES)
            return (i);
        i++;
    }
    return (NO_QUOTES_FOUND);
}

void    mix_quotes(char *from_single_quotes, char *from_double_quotes, char *str)
{
    // char *no_quotes;
   	// int quote_pos;
   	int i;
	int j;

    i = 0;
	j = 1;

    printf("mix_quotes: \n");

    if(from_single_quotes[i] && from_double_quotes[j])
    {
        printf("mix_quotes IF: \n");
        single_quotes(from_single_quotes,str);
    }
    else if(from_double_quotes[i] && from_single_quotes[j])
    {
        printf("mix_quotes ELSE: \n");
        double_quotes(from_double_quotes, str);
    }
} 

void	single_quotes(char *from_single_quotes, char *str)
{
    char *no_quotes;
   	int quote_pos;
   	int i;
	int j;
	
	i = 0;
	j = 0;
	no_quotes = ft_strtrim(from_single_quotes, "\'"); // "'jorge'"
	printf("SINGLE QUOTES - TRIM: %s\n", no_quotes);
    quote_pos = find_quote(str);
    while (str[i])
    {
    	if (str[i] == SQUOTES)
        {
    	    while (no_quotes[j])
			{
                str[quote_pos++] = no_quotes[j++];
			}
        	str[quote_pos] = '\0';
            break;
        }
        i++;
    }
}

void	double_quotes(char *from_double_quotes, char *str)
{
    char *no_quotes;
   	int quote_pos;
	int i;
	int j;
	
	i = 0;
	j = 0;
	no_quotes = ft_strtrim(from_double_quotes, "\"");
    printf("DOUBLE QUOTES - TRIM: %s\n", no_quotes);
    quote_pos = find_quote(str);
    while (str[i])
    {
    	if (str[i] == DQUOTES)
        {
    	    while (no_quotes[j])
			{
                str[quote_pos++] = no_quotes[j++];
			}
        	str[quote_pos] = '\0';
            break;
        }
        i++;
    }	
}

char *handle_quotes(char *str)
{
    char *from_single_quotes;
    char *from_double_quotes;
    if (str)
    {
        from_single_quotes = ft_strchr(str, SQUOTES);
        from_double_quotes = ft_strchr(str, DQUOTES);
        // if(from_single_quotes && from_double_quotes)
        //     mix_quotes(from_single_quotes, from_single_quotes, str);
        if (from_single_quotes)
            single_quotes(from_single_quotes, str);
        else if (from_double_quotes)
			double_quotes(from_double_quotes, str);
        printf("str: %s\n", str);
    }
    return (str);
}

*/

// aqui o código da Marce


// 2
int	count_tokens(t_data *data)
{
	int	i;
	int	space_count;
	int	single_quote_status;
	int	double_quote_status;

	i = -1;
	space_count = 0;
	single_quote_status = OFF;
	double_quote_status = OFF;
	while (data->input[++i])
	{
		if (data->input[i] == '\'')
		{
			if (single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = ON;
		}
		else if (data->input[i] == '\"')
		{
			if (double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = ON;
		}
		if (data->input[i] == ' ' && (!single_quote_status && !double_quote_status))
			space_count++;
	}
	data->token_count = space_count + 1;
	return (space_count + 1);
}


// 1
char	**look_for_quotes_and_split(t_data *data) //data->input
{
	int		i[3];
	int		single_quote_status;
	int		double_quote_status;
	char	**line_array;

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	single_quote_status = OFF;
	double_quote_status = OFF;
	line_array = malloc(sizeof(char *) * (count_tokens(data) + 1));
	line_array[count_tokens(data)] = NULL;
	while (data->input[++i[0]])
	{
		if (data->input[i[0]] == '\'')
		{
			if (single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = ON;
		}
		if (data->input[i[0]] == '\"')
		{
			if (double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = ON;
		}
		if (data->input[i[0]] != ' ' || (data->input[i[0]] == ' ' && (single_quote_status || double_quote_status)))
			i[1]++;
		if (i[1] && ((data->input[i[0] + 1] == '\0' || (data->input[i[0] + 1] == ' ' && (!single_quote_status && !double_quote_status)))))
		{
			line_array[i[2]++] = ft_substr(data->input + i[0] + 1 - i[1], 0, i[1]);
			i[1] = 0;
		}
	}
	return (line_array);
}

/*
// 4
void	remove_middle_quotes(char **command_block, int j)
{
	char    *first_part;
    char    *temp;

    first_part = ft_substr(*command_block, 0, j);
    temp = ft_strjoin(first_part, *command_block + j + 1);
    free(*command_block);
    free(first_part);
    *command_block = temp;
}

// 3
void	remove_token_quotes(t_command *command_list)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (command_list->command_block[i])
	{
		if (command_list->command_block[i][0] == '\'' || command_list->command_block[i][0] == '\"')
			command_list->command_block[i] = ft_substr(command_list->command_block[i], 1, ft_strlen(command_list->command_block[i]) - 2);
		while (command_list->command_block[i][j] != '\0')
		{
			if (command_list->command_block[i][j] == '\'' || command_list->command_block[i][j] == '\"')
				remove_middle_quotes(command_list->command_block, j);
			j++;
		}
		j = 0;
		i++;
	}
	if (command_list->next)
	{
		command_list = command_list->next;
		remove_token_quotes(command_list);
	}
}
*/