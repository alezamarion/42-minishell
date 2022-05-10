/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:04:49 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/04/28 00:01:33 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define HOME	0
#define OLDPWD	1

static int	too_many_arguments(char **str);
static void	chdir_to_path(t_data *data, int path);
static void	update_paths(t_data *data, char *old_dir);

int	cd(t_data *data, int id)
{
	char	*new_dir;
	char	*old_dir;

	if (too_many_arguments(data->argve[id]) || data->number_of_pipes)
		return (EXIT_FAILURE);
	new_dir = data->argve[id][1];
	old_dir = getcwd(NULL, 0);
	if (!new_dir || !ft_strcmp("~", new_dir))
		chdir_to_path(data, HOME);
	else if (!ft_strcmp("-", new_dir))
		chdir_to_path(data, OLDPWD);
	else if (chdir(new_dir))
	{
		ft_printf(STDERR, "Minishell: cd: %s: %s\n", new_dir, strerror(errno));
		ft_super_free((void **)&old_dir);
		return (EXIT_FAILURE);
	}
	update_paths(data, old_dir);
	ft_super_free((void **)&old_dir);
	return (EXIT_SUCCESS);
}

static int	too_many_arguments(char **str)
{
	if (ft_str_count(str) > 2)
	{
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	chdir_to_path(t_data *data, int path)
{
	t_vdt	vdt;

	if (path == HOME)
		vdt = find_in_list("HOME", data->vars);
	else
		vdt = find_in_list("OLDPWD", data->vars);
	if (chdir(vdt.value))
		ft_printf(STDERR, "Minishell: cd: %s: %s\n", vdt.value, strerror(errno));
}

static void	update_paths(t_data *data, char *old_dir)
{
	char	*curr_dir;
	t_vdt	vdt;

	curr_dir = getcwd(NULL, 0);
	vdt = find_in_list("OLDPWD", data->vars);
	update_envp(data, "OLDPWD", old_dir, vdt);
	change_in_list(data->vars, "OLDPWD", old_dir);
	vdt = find_in_list("PWD", data->vars);
	update_envp(data, "PWD", curr_dir, vdt);
	change_in_list(data->vars, "PWD", curr_dir);
	ft_super_free((void *)&curr_dir);
}
