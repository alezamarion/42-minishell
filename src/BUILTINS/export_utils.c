/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:00:43 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/24 23:22:02 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// alloc a bigger envp
// point older variables to new envp
int	relocate_envp(char **old_envp, char **new_envp, char *new_var)
{
	int	pos;

	pos = 0;
	while (*old_envp)
	{
		*new_envp = *old_envp;
		old_envp++;
		new_envp++;
		pos++;
	}
	*new_envp = ft_strdup(new_var);
	new_envp++;
	*new_envp = NULL;
	return (pos);
}

// calculates and allocate the new envp size
char	**new_bigger_envp(char **old_envp)
{
	int		envp_size;

	envp_size = ft_str_count(old_envp);
	envp_size += 2;
	return ((char **)malloc(sizeof(char **) * (envp_size)));
}

// reallocates envp when there is no var definition in input
void	upd_envp_w_def(t_data *data, int i, int id)
{
	char	**new_envp;
	int		pos;
	char	*name;
	t_vdt	vdt;

	name = get_var_name(data->argve[id][i]);
	vdt = find_in_list(name, data->vars);
	if (vdt.is_envp >= 0)
	{
		free(name);
		return ;
	}
	new_envp = new_bigger_envp(data->envp);
	pos = relocate_envp(data->envp, new_envp, data->argve[id][i]);
	free(data->envp);
	data->envp = new_envp;
	upd_idx_in_list(data->vars, name, pos);
	free(name);
}

// reallocates envp when there is a var definition in input
int	upd_envp_no_def(t_data *data, int i, int id)
{
	char	**new_envp;
	int		pos;
	char	*name;
	t_vdt	vdt;

	vdt = find_in_list(data->argve[id][i], data->vars);
	if (vdt.value == NULL || *vdt.value == '$')
		return (1);
	if (vdt.is_envp >= 0)
		return (0);
	else if (*vdt.value != '$')
	{
		new_envp = new_bigger_envp(data->envp);
		name = remount_var(data->argve[id][i], vdt.value);
		pos = relocate_envp(data->envp, new_envp, name);
		free(data->envp);
		data->envp = new_envp;
		upd_idx_in_list(data->vars, data->argve[id][i], pos);
		free(name);
		return (0);
	}
	else
		return (1);
}
