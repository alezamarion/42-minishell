/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:53:52 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/10 10:43:56 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_extra_spaces(t_data *data)
{
	char	**splitted_spaces;
	int		len;
	int		i;

	splitted_spaces = ft_split(data->input, ' ');
	if (!splitted_spaces)
		exit_minishell(data, FAILURE);
	i = 0;
	len = 0;
	while (splitted_spaces[i])
		len += ft_strlen(splitted_spaces[i++]) + 1;
	free(data->input);
	data->input = (char *)malloc(sizeof(char) * len);
	if (!data->input)
		exit_minishell(data, FAILURE);
	i = 0;
	data->input[0] = 0;
	while (splitted_spaces[i])
	{
		ft_strcat(data->input, splitted_spaces[i]);
		if (splitted_spaces[++i])
			ft_strcat(data->input, " ");
	}
	double_free((void ***)&splitted_spaces);
}
