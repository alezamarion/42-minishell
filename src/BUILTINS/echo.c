/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:11:16 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/21 19:22:21 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void echo(t_data *data)
{
    int break_line;
	int index;

    break_line = TRUE;

    if (data->argve[0][1]) // parsed_str[0])
    {
		index = 1;
        if (!ft_strncmp(data->argve[0][index], "-n", 3))
		{
			break_line = FALSE;
			index = 2;
		}            
        while (data->argve[0][index])
        {
            ft_putstr_fd(data->argve[0][index], 1);
            ft_putchar_fd(' ', 1);
            index++;
        }
        if (break_line)
            ft_putstr_fd("\n", 1);
    }
    else
        ft_putstr_fd("\n", 1);
}