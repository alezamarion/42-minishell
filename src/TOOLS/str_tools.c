/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:54:50 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/02 23:15:44 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Vamos usar funcoes proprias
/* DICA: Usar "new" como argumento onde este é alocado
* para mapeamento de leak
*/
int	ft_strcpy_handled(char **new, char const *src)
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
	int		count;

	count = 0;
	if (str)
	{
		while (str[count])
			count++;
	}
	return (count);
}

// tratada: libera string antiga - adiciona s2 ao final de s1
int	ft_strjoin_handled(char **s1, char const *s2)
{
	size_t	len;
	size_t	k;
	char	*s;

	if (!*s1 || !s2)
		return (FAILURE);
	len = ft_strlen(*s1) + ft_strlen(s2) + 1;
	s = (char *)malloc(len * sizeof(char));
	if (!s)
		return (FAILURE);
	k = ft_strlen(*s1);
	ft_strlcpy(s, *s1, k + 1);
	ft_strlcpy(s + k, s2, len - k);
	s[len - 1] = '\0';
	free(*s1);
	*s1 = s;
	return (SUCCESS);
}

/*
	Retira da str o que está entre init e end, deixando apenas as extremidades.
	Eg. str = "Paralelepipedo"
	ft_strcut(&str, 4, 8);
	str ==> "Parapipedo"
*/
void	ft_strcut(char **str, size_t init, size_t end)
{
	char	*first;
	char	*second;

	if (init)
		first = ft_substr(*str, 0, init);
	else
		first = ft_strdup("");
	if (end < ft_strlen(*str))
		second = ft_substr(*str, end, ft_strlen(*str));
	else
		second = ft_strdup("");
	free(*str);
	*str = ft_strjoin(first, second);
	free(first);
	free(second);
	first = NULL;
	second = NULL;
}

// remount var from var_name + '=' + var_value
char	*remount_var(char *var_name, char *var_value)
{
	char	*name;

	name = ft_strdup(var_name);
	ft_strjoin_handled(&name, "=");
	ft_strjoin_handled(&name, var_value);
	return (name);
}
