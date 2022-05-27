/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:31:09 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/10 10:43:46 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DIFF_REDIR	"minishell: syntax error near unexpected token `%c'"
#define BL_IN_REDIR	"minishell: syntax error near unexpected token `newline'"

static void	malloc_file(t_data *data, int string_level, int k, int bytes);
static int	count_redirects(char *str);
static int	save_file(char *cmd, char **file);
static void	find_redirects(t_data *data, int id);

int	pull_redirects(t_data *data)
{
	int		id;
	int		redirects_nbr;

	id = 0;
	malloc_file(data, 0, 0, data->number_of_pipes + 2);
	while (data->cmds_piped[id])
	{
		redirects_nbr = count_redirects(data->cmds_piped[id]);
		if (redirects_nbr == -1)
		{
			g_status_code = SINTAX_ERR;
			return (FAILURE);
		}
		malloc_file(data, 1, id, redirects_nbr + 1);
		if (redirects_nbr)
			find_redirects(data, id);
		unmask_character(data->cmds_piped[id], 4, '>');
		unmask_character(data->cmds_piped[id], 5, '<');
		id++;
	}
	return (SUCCESS);
}

static void	find_redirects(t_data *data, int id)
{
	int		j;
	int		k;
	int		init;

	j = -1;
	k = 0;
	while (data->cmds_piped[id][++j])
	{
		if (!ft_strchr("><", data->cmds_piped[id][j]))
			continue ;
		init = j;
		if (data->cmds_piped[id][j] == '>')
			data->file_mode[id][k] = GREAT;
		else if (data->cmds_piped[id][j] == '<')
			data->file_mode[id][k] = LESS;
		if (data->cmds_piped[id][j] == data->cmds_piped[id][j + 1])
			data->file_mode[id][k] *= 2;
		j += 1 + (!(data->file_mode[id][k] % 2));
		j += save_file(data->cmds_piped[id] + j, &data->file[id][k]);
		ft_strcut(&data->cmds_piped[id], init, j);
		j = init - 1;
		if (!data->file[id][k] || !data->cmds_piped[id])
			exit_minishell(data, FAILURE);
		k++;
	}
}

static int	save_file(char *cmd, char **file)
{
	int		end;
	int		init;

	end = 0;
	while (cmd[end] == ' ' && cmd[end])
		end++;
	init = end;
	while (!ft_strchr(" ><", cmd[end]) && cmd[end])
		end++;
	if (cmd[end])
		end--;
	*file = ft_substr(cmd, init, end);
	if (cmd[end])
		end++;
	return (end);
}

static int	count_redirects(char *s)
{
	int		i;
	int		j;
	int		redirects_nbr;

	i = -1;
	redirects_nbr = 0;
	while (s[++i])
	{
		if (s[i] != '>' && s[i] != '<')
			continue ;
		j = i;
		while (ft_strchr("><", s[i]) && s[i])
			i++;
		if ((s[j] != s[j + 1] && ft_strchr("><", s[j + 1])) || i - j > 2)
			ft_printf(STDERR, DIFF_REDIR, s[i + 1 + (j - i > 2)]);
		else if (!s[i])
			ft_printf(STDERR, BL_IN_REDIR);
		else
		{
			redirects_nbr++;
			continue ;
		}
		return (-1);
	}
	return (redirects_nbr);
}

static void	malloc_file(t_data *data, int string_level, int id, int bytes)
{
	if (!string_level)
	{
		data->file = (char ***)ft_calloc(sizeof(char **), bytes);
		data->file_mode = (char **)ft_calloc(sizeof(char *), bytes);
		if (!data->file || !data->file_mode)
			exit_minishell(data, FAILURE);
	}
	else
	{
		data->file[id] = (char **)ft_calloc(sizeof(char *), bytes);
		data->file_mode[id] = (char *)ft_calloc(sizeof(char), bytes);
		if (!data->file[id] || !data->file_mode[id])
			exit_minishell(data, FAILURE);
	}
}
