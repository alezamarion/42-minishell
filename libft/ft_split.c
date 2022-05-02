/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:25:35 by azamario          #+#    #+#             */
/*   Updated: 2022/04/20 18:12:49 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	count_words(const char *s, char c)
// {
// 	int	i;
// 	int	n_word;
// 	int	control;

// 	i = 0;
// 	control = 0;
// 	n_word = 0;
// 	while (s[0] != '\0' && s[i] != '\0')
// 	{
// 		if (s[i] != c && control == 0)
// 		{
// 			control = 1;
// 			n_word++;
// 		}
// 		else if (s[i] == c)
// 			control = 0;
// 		i++;
// 	}
// 	return (n_word);
// }

// static char	*string(const char *s, int init, int end)
// {
// 	char	*string;
// 	int		i;
// 	int		offset;

// 	i = 0;
// 	string = (char *)malloc((end - init + 1) * sizeof(char));
// 	offset = end - init;
// 	while (i < offset)
// 	{
// 		string[i] = s[init + i];
// 		i++;
// 	}
// 	string[i] = '\0';
// 	return (string);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**split;
// 	int		init_w;
// 	size_t	i;
// 	size_t	j;

// 	if (s == 0)
// 		return (NULL);
// 	i = -1;
// 	j = 0; 
// 	init_w = -1;
// 	split = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
// 	if (split == 0)
// 		return (NULL);
// 	while (++i <= ft_strlen(s))
// 	{
// 		if (s[i] != c && init_w < 0)
// 			init_w = i;
// 		else if ((s[i] == c || i == ft_strlen(s)) && init_w >= 0)
// 		{
// 			split[j++] = string(s, init_w, i);
// 			init_w = -1;
// 		}
// 	}
// 	split[j] = NULL;
// 	return (split);
// }


// vlima-nu

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	num_of_words(char const *s, char c)
{
	int	total;
	int	i;

	i = 0;
	total = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		total++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (total);
}

static char	*next_word(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return ((char *)s);
}

char	**ft_split(char const *s, char c)
{
	char	**final;
	size_t	i;
	size_t	words;

	if (s != NULL)
	{
		words = num_of_words(s, c);
		final = (char **)malloc(sizeof(char *) * (words + 1));
		if (!(final))
			return (NULL);
		i = 0;
		while (i < words)
		{
			s = next_word(s, c);
			final[i] = ft_substr(s, 0, ft_wordlen(s, c));
			if (!final[i])
				return (NULL);
			i++;
			s += ft_wordlen(s, c);
		}
		final[words] = NULL;
		return (final);
	}
	return (NULL);
}
