/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:31:09 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/04/25 03:08:04 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define DIFF_REDIR		"minishell: syntax error near unexpected token `%c'"
#define BL_IN_REDIR	"minishell: syntax error near unexpected token `newline'"

static void	malloc_file(t_data *data, int string_level, int k, int bytes);
static int	count_redirects(t_data *data, char *str);
static int	save_file(char *cmd, char **file);
static void	find_redirects(t_data *data, int id);

// void	debug_redirects(t_data *data)
// {
// 	int		id;
// 	int		k;

// 	id = 0;
// 	while (data->file[id])
// 	{
// 		k = -1;
// 		printf("\nid:%d\n", id);
// 		while (data->file[id][++k])
// 			printf("\n%d %s\n", data->file_mode[id][k], data->file[id][k]);
// 		printf("\n%s-", data->cmds_piped[id]);
// 		printf("cmd_len:%ld\n", strlen(data->cmds_piped[id]));
// 		id++;
// 	}
// }

void	fill_redirects(t_data *data)
{
	int		id;
	int		redirects_nbr;

	id = 0;
	malloc_file(data, 0, 0, data->number_of_pipes + 1);
	while (data->cmds_piped[id])
	{
		redirects_nbr = count_redirects(data, data->cmds_piped[id]);
		if (redirects_nbr)
		{
			malloc_file(data, 1, id, redirects_nbr + 1);
			find_redirects(data, id);
		}
		id++;
	}
	id = 0;
	while (data->cmds_piped[id])
	{
		reverse_char(data->cmds_piped[id], 4, '>');
		reverse_char(data->cmds_piped[id], 5, '<');
		id++;
	}
	// debug_redirects(data);
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
		ft_strcut(&data->cmds_piped[id], init - 1, j + 1);
		if (!data->file[id][k])
			exit_minishell(data, FAILURE);
		k++;
	}
}

static int	save_file(char *cmd, char **file)
{
	int		total;
	int		init;

	total = 0;
	while (cmd[total] == ' ' && cmd[total])
		total++;
	init = total;
	while (!ft_strchr(" ><", cmd[total]) && cmd[total])
		total++;
	*file = ft_substr(cmd, init, total);
	return (total - 1);
}

static int	count_redirects(t_data *data, char *s)
{
	int		i;
	int		aux;
	int		redirects_nbr;

	i = -1;
	redirects_nbr = 0;
	while (s[++i])
	{
		if (s[i] != '>' && s[i] != '<')
			continue ;
		aux = i;
		while (ft_strchr("><", s[aux]) && s[aux])
			aux++;
		if ((s[i] != s[i + 1] && ft_strchr("><", s[i + 1])) || aux - i > 2)
			printf(DIFF_REDIR, s[i + 1 + (aux - i > 2)]);
		else if (!s[aux])
			printf(BL_IN_REDIR);
		else
		{
			i += aux - i;
			redirects_nbr++;
			continue ;
		}
		exit_minishell(data, FAILURE);
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
