/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:32:15 by ocarlos-          #+#    #+#             */
/*   Updated: 2022/05/24 20:32:42 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_export(char **envp);
static int	invalid_var(char ***argve, int id, int n);
static int	isdigitvar(char *vardefinition);
static void	printmsg(char *str);

void	export(t_data *data, int id)
{
	int		i;
	int		strsize;

	i = 0;
	while (data->argve[id][i])
	{
		strsize = ft_strlen(data->argve[id][i]);
		strsize--;
		if (is_builtins(data->argve[id][i]) == 0)
		{
			if (invalid_var(data->argve, id, i))
				printmsg(data->argve[id][i]);
			else if (data->argve[id][i][strsize] == '=')
				printmsg(data->argve[id][i]);
			else if (ft_strchr(data->argve[id][i], '='))
				upd_envp_w_def(data, i, id);
			else if (upd_envp_no_def(data, i, id))
				printmsg(data->argve[id][i]);
		}
		else if (!(data->argve[id][i + 1]))
			sort_export(data->envp);
		i++;
	}
}

// sorts envp content and prints on screen
static void	sort_export(char **envp)
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

// checks if expression is "export $" or var is number -> invalid input
static int	invalid_var(char ***argve, int id, int n)
{
	if (ft_strcmp(argve[id][0], "export") == 0 &&
		(ft_strcmp(argve[id][1], "$") == 0 ||
		ft_strcmp(argve[id][1], "=") == 0) &&
		argve[id][2] == 0x0)
		return (TRUE);
	else if (ft_strcmp(argve[id][0], "export") == 0 && \
	(isdigitvar(argve[id][n]) || !ft_isalpha(argve[id][n][0])))
		return (TRUE);
	else
		return (FALSE);
}

static int	isdigitvar(char *vardefinition)
{
	while (*vardefinition && *vardefinition != '=')
	{
		if (!ft_isdigit(*vardefinition))
			return (FALSE);
		vardefinition++;
	}
	return (TRUE);
}

void	printmsg(char *str)
{
	printf("Minishell: export: ");
	printf("`%s': not a valid identifier\n", str);
}
