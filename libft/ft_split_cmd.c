/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:37:36 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 08:13:40 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c, int i, int type)
{
	int	count;

	count = 0;
	while (type == 0 && s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = find_qouts(s, i - 1, i);
		if ((((s[i] >= 1 && s[i] <= 126) && s[i] != c) && s[i + 1] == c)
			|| (((s[i] >= 1 && s[i] <= 126) && s[i] != c) && s[i + 1] == '\0'))
			break ;
		i++;
	}
	if (type == 0)
		return (i);
	count = 0;
	while (type == 1 && s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = find_qouts(s, i - 1, i);
		if ((((s[i] >= 1 && s[i] <= 126) && s[i] != c) && s[i + 1] == c)
			|| (((s[i] >= 1 && s[i] <= 126) && s[i] != c) && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*make_string(char const *s, int start, int end)
{
	int		size;
	char	*string;
	int		length;

	size = end - start + 1;
	length = 0;
	string = malloc(size + 1);
	if (!string)
		return (NULL);
	while (start <= end)
	{
		string[length] = s[start];
		start++;
		length++;
	}
	string[length] = '\0';
	return (string);
}

static char	**process(char const *s, char c, char **string, int i)
{
	int	start;
	int	end;

	start = 0;
	while (s[start] != '\0')
	{
		while (s[start] == c)
			start++;
		if (s[start] == '\0')
			break ;
		end = count(s, c, start, 0);
		string[i] = make_string(s, start, end);
		if (!string[i])
		{
			while (i > 0)
				free(string[--i]);
			free(string);
			return (NULL);
		}
		i++;
		start = end + 1;
	}
	string[i] = NULL;
	return (string);
}

char	**ft_split_cmd(char const *s, char c)
{
	char	**string;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (*s == '\0')
	{
		string = (char **)malloc(sizeof(char *));
		if (string != NULL)
			string[0] = NULL;
		return (string);
	}
	string = (char **)malloc((count(s, c, 0, 1) + 1) * sizeof(char *));
	if (!string)
		return (NULL);
	string = process(s, c, string, i);
	return (string);
}

/*
int	main(void)
{
	char	**result;
	int		i;

	//test1 = "\0mohammad";
	//test2 = NULL;
	//test3 = when the memory size is small
	//test4 = "cccmohammad";  c = 'c';
	result = ft_split("hello world this is a test", ' ');
	i = 0;
	while (result[i])
	{
		printf("%s\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/