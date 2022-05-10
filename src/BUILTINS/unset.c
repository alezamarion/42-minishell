/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:39:44 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/04/27 15:03:43 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	debug_unset(t_data *data)
// {
// 	t_vars	*aux;
// 	int		i;

// 	i = 0;
// 	while (data->envp[i])
// 		printf("%s\n", data->envp[i++]);
// 	printf("\nStruct:\n\n");
// 	aux = data->vars;
// 	while (aux)
// 	{
// 		printf("%s\n", aux->var_name);
// 		aux = aux->next;
// 	}
// }

void	unset(t_data *data, int id)
{
	int		i;
	int		arg;

	arg = 1;
	while (data->argve[id][arg])
	{
		i = 0;
		while (data->envp[i])
		{
			if (!ft_strncmp(data->envp[i], data->argve[id][arg], \
				ft_strlen(data->argve[id][arg])))
			{
				free(data->envp[i]);
				while (data->envp[i])
				{
					data->envp[i] = data->envp[i + 1];
					i++;
				}
				data->envp[i] = 0;
			}
			else
				i++;
		}
		delete_in_list(data->argve[id][arg++], &data->vars);
	}
}
