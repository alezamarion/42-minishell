/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:30:10 by ocarlos-          #+#    #+#             */
/*   Updated: 2022/05/02 23:04:46 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// gets and returns the name of the variable
char	*get_var_name(char *input)
{
	int		i;
	int		space;
	char	*name;

	i = 0;
	space = 0;
	while (input[i] != '=')
	{
		i++;
		if (input[i] == ' ')
			space = i;
	}
	name = (char *)malloc((i - space) * sizeof(char));
	if (space)
	{
		while (*input != ' ')
			input++;
		space++;
		input++;
	}
	ft_strlcpy(name, input, (i - space) + 1);
	return (name);
}

// gets and returns the value of the variable
char	*get_var_value(char *input)
{
	int		i;
	char	*value;

	i = 0;
	while (*input != '=')
		input++;
	input++;
	if (*input == '\"')
	{
		input++;
		while (input[i] != '\"' && input[i])
			i++;
	}
	else
		while (input[i])
			i++;
	value = (char *)malloc(i * sizeof(char) + 1);
	ft_strlcpy(value, input, i + 1);
	return (value);
}

void	update_envp(t_data *data, char *name, char *value, t_vdt vdt)
{
	int		var_size;
	int		name_size;
	int		value_size;
	char	*new_var;

	name_size = ft_strlen(name);
	value_size = ft_strlen(value);
	var_size = name_size + value_size + 2;
	new_var = malloc(sizeof(char) * var_size);
	ft_strlcpy(new_var, name, name_size + 1);
	ft_strlcat(new_var, "=", name_size + 3);
	ft_strlcat(new_var, value, value_size + name_size + 4);
	free(data->envp[vdt.is_envp]);
	data->envp[vdt.is_envp] = new_var;
}

// checks for variables in the input string and stores them on a linked list
void	grab_vars(t_data *data, char *str)
{
	char	*name;
	char	*value;
	t_vdt	vdt;

	if (ft_strchr(str, '='))
	{
		data->exec_flag = -1;
		name = get_var_name(str);
		value = get_var_value(str);
		if (!data->vars)
			data->vars = new_node(name, value);
		else
		{
			vdt = find_in_list(name, data->vars);
			if (ft_strcmp(vdt.value, "$") == 0)
				add_to_list(&data->vars, name, value);
			else
			{
				if (vdt.is_envp >= 0)
					update_envp(data, name, value, vdt);
				change_in_list(data->vars, name, value);
			}
		}
		free(name);
		free(value);
	}
}
