/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_take_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:56:26 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/30 23:28:31 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void prompt(t_data *data)
{
	char	cwd[1024];
	char	*prompt;

	data->username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	data->username = ft_strjoin(data->username, ":~");
	prompt = ft_strjoin(data->username, cwd);
	printf("\n%s%s:$ ", KBLU, prompt);
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
	char	*old_input;
	int		status;
	
	prompt(data);
	data->input = readline("");
	if (strlen(data->input) != 0)
	{
		old_input = data->input;
		put_on_history(data->input, old_input);
		status = ft_strcpy_handled(&data->input, data->input);
		if (status == FAILURE)
			exit_minishell(data, FAILURE);
		//free(buf); ---> acho q readline já faz isso
		return (SUCCESS);
	}
	else
		return (FAILURE);
}