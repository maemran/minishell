/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qouts_with_dollar_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:39:24 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:39 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit_double_qouts(char **array, int *spaces)
{
	if (spaces)
		free(spaces);
	ft_free_tow_d_array(array);
	return (FAILURE);
}

char	*join_two_d_to_string(char **cmds, char *c)
{
	int		i;
	char	*string;
	char	*temp1;
	char	*temp2;

	i = 1;
	string = ft_strdup(cmds[0]);
	if (!string)
		return (NULL);
	while (cmds[i])
	{
		temp2 = ft_strjoin(c, cmds[i]);
		temp1 = ft_strjoin(string, temp2);
		free(temp2);
		free(string);
		if (!temp1)
			return (NULL);
		string = temp1;
		i++;
	}
	return (string);
}

char	*add_single(char *str, int type)
{
	char	*string;
	int		i;

	i = 0;
	string = mem_alloc(str, type, 0);
	if (!string)
		return (NULL);
	string[0] = '\'';
	while (str[i])
	{
		string[i + 1] = str[i];
		i++;
	}
	if (type == 1)
		string[i + 1] = '\0';
	else if (type == 0)
	{
		string[i + 1] = '\'';
		string[i + 2] = '\0';
	}
	free(str);
	return (string);
}

char	*mem_alloc(char *str, int type, int n)
{
	char	*string;

	string = NULL;
	if (type == 1)
		string = malloc(sizeof(char) * (ft_strlen(str) + (2 + n)));
	else if (type == 0)
		string = malloc(sizeof(char) * (ft_strlen(str) + (3 + n)));
	return (string);
}

char	*add_single_with_dollar(char *str, int type)
{
	char	*string;
	int		i;

	i = 0;
	string = mem_alloc(str, type, 1);
	if (!string)
		return (NULL);
	string[0] = '$';
	string[1] = '\'';
	while (str[i])
	{
		string[i + 2] = str[i];
		i++;
	}
	if (type == 1)
		string[i + 2] = '\0';
	else if (type == 0)
	{
		string[i + 2] = '\'';
		string[i + 3] = '\0';
	}
	free(str);
	return (string);
}
