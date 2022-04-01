/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:30:10 by ocarlos-          #+#    #+#             */
/*   Updated: 2022/03/24 12:34:30 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_var_name(char *input)
{
	int		i;
	char	*name;

	i = 0;
	while (input[i] != '=')
		i++;
	name = (char *)malloc(i * sizeof(char) + 1);
	ft_strlcpy(name, input, i + 1);
	return (name);
}

char	*get_var_value(char *input)
{
	int		i;
	char	*value;

	i = 0;
	while (*input != '=')
		input++;
	input++;
	while (input[i] != ' ' && input[i])
		i++;
	value = (char *)malloc(i * sizeof(char) + 1);
	ft_strlcpy(value, input, i + 1);
	return (value);
}

void	grab_vars(t_data *data)
{
	char *str;
	char *name;
	char *value;

	str = data->input;
	if (ft_strchr(str, '='))
	{
		data->exec_flag = -1;
		while (*str != '=')
			str++;
		while (*str != ' ' && str != data->input)
			str--;
		if (*str == ' ') 
			str++;
		name = get_var_name(str);
		value = get_var_value(str);
		if (!data->vars)
			data->vars = new_node(name, value);
		else
			add_to_list(&data->vars, name, value);
		free(name);
		free(value);
	}
}