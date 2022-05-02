/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_take_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:56:26 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/23 13:25:59 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	prompt(t_data *data)
{
	char	cwd[1024];
	char	*buf;
	char	*prompt_str;
	char	*path;

	data->username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	buf = ft_strjoin("\e[32m", data->username);
	prompt_str = ft_strjoin(buf, ":\e[39m");
	path = ft_strjoin("\e[35m", cwd);
	free(buf);
	buf = ft_strjoin(prompt_str, path);
	free(prompt_str);
	prompt_str = ft_strjoin(buf, "\e[39m$ ");
	data->input = readline(prompt_str);
	free(buf);
	free(prompt_str);
	free(path);
}

//Function to print Current Directory.
void	print_dir(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("Dir: %s\n", cwd);
}

/** Function to take input - MALLOC input*/
int	take_input(t_data *data)
{
	prompt(data);
	if (!data->input)
		exit_minishell(data, FAILURE);
	if (ft_strlen(data->input) != 0)
	{		
		put_on_history(data->input, data->old_input);
		if (data->old_input)
			free(data->old_input);
		data->old_input = ft_strdup(data->input);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}
