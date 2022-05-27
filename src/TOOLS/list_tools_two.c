/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:24:13 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/12 22:08:08 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// changes the value of an existing variable on the list
void	change_in_list(t_vars *lst, char *var_name, char *var_value)
{
	if (lst != 0x0)
	{
		while (lst)
		{
			if (ft_strcmp(var_name, lst->var_name) == 0)
			{
				free(lst->var_value);
				lst->var_value = ft_strdup(var_value);
				return ;
			}
			lst = lst->next;
		}
	}
}

// deletes an item in list
void	delete_in_list(char *var_name, t_vars **vars)
{
	t_vars	*temp;
	t_vars	*prev;

	temp = *vars;
	prev = temp;
	if (temp && !ft_strcmp(var_name, temp->var_name))
	{
		*vars = temp->next;
		free(temp->var_name);
		free(temp->var_value);
		free(temp);
		return ;
	}
	while (temp && ft_strcmp(var_name, temp->var_name))
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
	free(temp->var_name);
	free(temp->var_value);
	free(temp);
}

// updates the envp index in a list item
void	upd_idx_in_list(t_vars *lst, char *var_name, int pos)
{
	if (lst != 0x0)
	{
		while (lst)
		{
			if (ft_strcmp(var_name, lst->var_name) == 0)
			{
				lst->env = pos;
				return ;
			}
			lst = lst->next;
		}
	}
}
