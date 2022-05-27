/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:04:49 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/19 21:06:31 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	too_many_arguments(char **str);
static int	chdir_to_oldpwd(t_vars *vars);
static int	chdir_to_home(char *cwd, t_vars *vars);
static void	update_paths(t_data *data, char *old_dir);

int	cd(t_data *data, int id)
{
	char	*new_dir;
	char	*old_dir;
	int		status;

	status = 0;
	if (too_many_arguments(data->argve[id]))
		return (EXIT_FAILURE);
	new_dir = data->argve[id][1];
	old_dir = getcwd(NULL, 0);
	if (!new_dir || *new_dir == '~')
		status = chdir_to_home(data->argve[id][1], data->vars);
	else if (!ft_strcmp("-", new_dir))
		status = chdir_to_oldpwd(data->vars);
	else if (chdir(new_dir))
	{
		ft_printf(STDERR, "Minishell: cd: %s: %s\n", new_dir, strerror(errno));
		ft_super_free((void **)&old_dir);
		g_status_code = 1;
		return (EXIT_FAILURE);
	}
	update_paths(data, old_dir);
	ft_super_free((void **)&old_dir);
	return (status);
}

static int	too_many_arguments(char **str)
{
	if (ft_str_count(str) > 2)
	{
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
		g_status_code = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	chdir_to_home(char *cwd, t_vars *vars)
{
	t_vdt	vdt;
	char	*new_cwd;

	vdt = find_in_list("HOME", vars);
	if (!vdt.value)
	{
		ft_printf(STDERR, "Minishell: cd: HOME not set\n");
		return (FAILURE);
	}
	if (!cwd)
		new_cwd = ft_strdup(vdt.value);
	else
		new_cwd = ft_strjoin(vdt.value, ++cwd);
	if (chdir(new_cwd))
	{
		g_status_code = 1;
		ft_printf(STDERR, "Minishell: cd: %s: %s\n", new_cwd, strerror(errno));
		free(new_cwd);
		return (FAILURE);
	}
	free(new_cwd);
	return (SUCCESS);
}

static int	chdir_to_oldpwd(t_vars *vars)
{
	t_vdt	vdt;

	vdt = find_in_list("OLDPWD", vars);
	if (!vdt.value)
	{
		ft_printf(STDERR, "Minishell: cd: OLDPWD not set\n");
		return (FAILURE);
	}
	ft_printf(STDOUT, "%s\n", vdt.value);
	if (chdir(vdt.value))
	{
		g_status_code = 1;
		ft_printf(STDERR, "Minishell: cd: %s: %s\n", vdt.value, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
