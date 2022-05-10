/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:32:15 by ocarlos-          #+#    #+#             */
/*   Updated: 2022/05/04 01:07:56 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		return ;
	new_envp = new_bigger_envp(data->envp);
	pos = relocate_envp(data->envp, new_envp, data->argve[id][i]);
	free(data->envp);
	data->envp = new_envp;
	upd_idx_in_list(data->vars, name, pos);
	free(name);
}

// reallocates envp when there is a var definition in input
void	upd_envp_no_def(t_data *data, int i, int id)
{
	char	**new_envp;
	int		pos;
	char	*name;
	t_vdt	vdt;

	vdt = find_in_list(data->argve[id][i], data->vars);
	if (vdt.is_envp >= 0)
		return ;
	if (*vdt.value != '$')
	{
		new_envp = new_bigger_envp(data->envp);
		name = remount_var(data->argve[id][i], vdt.value);
		pos = relocate_envp(data->envp, new_envp, name);
		free(data->envp);
		data->envp = new_envp;
		upd_idx_in_list(data->vars, data->argve[id][i], pos);
		free(name);
	}
}

// sorts envp content and prints on screen
void	sort_export(char **envp)
{
	char	**temp_envp;
	int		i;
	int		last;

	temp_envp = envp;
	temp_envp = new_bigger_envp(envp);
	i = relocate_envp(envp, temp_envp, "----temp----");
	last = i--;
	free(temp_envp[last]);
	while (i > 0)
	{
		if (ft_strcmp(temp_envp[i], temp_envp[i - 1]) < 0)
		{
			temp_envp[last] = temp_envp[i];
			temp_envp[i] = temp_envp[i - 1];
			temp_envp[i - 1] = temp_envp[last];
			i = last;
		}
		i--;
	}
	while (i < last)
		printf("declare -x %s\n", temp_envp[i++]);
	free(temp_envp);
}

// checks if expression is "export $", an invalid input
int		invalid_var(char ***argve, int id)
{
	if (ft_strcmp(argve[id][0], "export") == 0 && 
		ft_strcmp(argve[id][1], "$") == 0 &&
		argve[id][2] == 0x0)
		return TRUE;
	else
		return FALSE;
}

void	export(t_data *data, int id)
{
	int		i;

	i = 0;
	while (data->argve[id][i])
	{
		if (is_builtins(data->argve[id][i]) == 0)
		{
			if (invalid_var(data->argve, id))
				printf("bash: export: `$': not a valid identifier\n");
			else if (ft_strchr(data->argve[id][i], '='))
				upd_envp_w_def(data, i, id);
			else 
				upd_envp_no_def(data, i, id);
		}
		else if (!(data->argve[id][i + 1]))
			sort_export(data->envp);
		i++;
	}
}
