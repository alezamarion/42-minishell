/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:54:50 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/24 12:33:41 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Vamos usar funcoes proprias
/* DICA: Usar "new" como argumento onde este é alocado
* para mapeamento de leak
*/
int ft_strcpy_handled(char **new, char const *src)
{
	size_t	len;
	int		i;

	len = ft_strlen(src);
	if (!*new)
		*new = (char *)malloc(len * sizeof(char) + 1);
	if (!*new)
	{
		perror("malloc error");
		return (FAILURE);
	}
	i = 0;
	while (src[i])
	{
		(*new)[i] = src[i];
		if (src[i])
			i++;	
	}
	(*new)[i] = '\0';
	return (SUCCESS);
}

//conta strings em char**
int	ft_str_count(char **str)
{
	int count;

	count = 0;
	if (str)
	{
		while(str[count])
			count++;
	}
	return (count);
}

void free_str(char **str) //Uso: passar endereço da str
{
    if (str)
    {
        if (*str)
        {
            free(*str);
            *str = NULL;
        }
        str = NULL;
    }
}

void free_double_str(char ***str) //Uso: passar endereço da **str
{
    if (str)
    {
        free_str(*str);
        *str = NULL;
    }    
}

void free_triple_str(char ****str) //Uso: passar endereço da ***str
{
    if (str)
    {
        free_double_str(*str);
        *str = NULL;
    }    
}
