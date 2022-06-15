
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	count_words(const char *s, char c)
{
	int	i;
	int	n_word;
	int	control;

	i = 0;
	control = 0;
	n_word = 0;
	while (s[0] != '\0' && s[i] != '\0')
	{
		if (s[i] != c && control == 0)
		{
			control = 1;
			n_word++;
		}
		else if (s[i] == c)
			control = 0;
		i++;
	}
	return (n_word);
}

static char	*string(const char *s, int init, int end)
{
	char	*string;
	int		i;

	i = 0;
	string = (char *)malloc((end - init + 1) * sizeof(char));
	while (end > init)
	{
		string[i] = s[init];
		i++;
		init++;
	}
	string[i] = '\0';
	return (string);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		init_w;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (NULL);
	i = -1;
	j = 0;
	init_w = -1;
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (split == 0)
		return (NULL);
	while (++i <= strlen(s))
	{
		if (s[i] != c && init_w < 0)
			init_w = i;
		else if ((s[i] == c || i == strlen(s)) && init_w >= 0)
		{
			split[j++] = string(s, init_w, i);
			init_w = -1;
		}
	}
	split[j] = NULL;
	return (split);
}

int main(void)
{
    char *str = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
    char **result;
    
    result = ft_split(str, ':');
	while (result)
	{
		printf("result is : %s\n", *result);
		result++;
	}
//	printf("result is %s\n", *result);
    // printf("result 1 is : %s\n", *result);
    // result++;   
    // printf("result 2 is : %s\n", *result);
    // result++;   
    // printf("result 3 is : %s\n", *result);
    
}

/*

result[0] = "ls -l\0";
result[1] = " wc";
result[2] = NULL;

*/
