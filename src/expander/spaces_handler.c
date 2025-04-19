/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:16:39 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:58 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_spaces(char *string, int n)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	temp = malloc(sizeof(char) * (n + 1));
	if (!temp)
		return (NULL);
	while (i < n)
	{
		temp[i] = ' ';
		i++;
	}
	temp[i] = '\0';
	temp2 = ft_strjoin(temp, string);
	free(temp);
	return (temp2);
}

char	*join_spaces_loop(int *i, char **cmds, int *spaces)
{
	char	*temp1;
	char	*temp2;
	char	*string;

	string = ft_strdup("");
	while (cmds[*i])
	{
		temp1 = join_spaces(cmds[*i], spaces[*i]);
		temp2 = ft_strjoin(string, temp1);
		if (!temp2)
		{
			free(string);
			free(temp1);
			return (NULL);
		}
		free(temp1);
		free(string);
		string = temp2;
		(*i)++;
	}
	return (string);
}

char	*join_spaces_before(char **cmds, int *spaces)
{
	int		i;
	char	*string;
	char	*temp1;
	char	*temp2;

	i = 0;
	string = join_spaces_loop(&i, cmds, spaces);
	if (!string)
		return (NULL);
	if (spaces[i] != -1)
	{
		temp1 = join_spaces("", spaces[i]);
		temp2 = ft_strjoin(string, temp1);
		if (!temp2)
		{
			free(string);
			free(temp1);
			return (NULL);
		}
		free(temp1);
		free(string);
		string = temp2;
	}
	return (string);
}

char	*join_with_num_of_spaces2(char **cmds, int *spaces, char *string)
{
	char	*temp1;
	char	*temp2;
	int		i;

	i = 1;
	while (cmds[i])
	{
		if (i < ft_two_d_len(cmds))
			temp1 = join_spaces(cmds[i], spaces[i - 1]);
		else
			temp1 = ft_strdup(cmds[i]);
		temp2 = ft_strjoin(string, temp1);
		if (!temp2)
		{
			free(temp1);
			free(string);
			return (NULL);
		}
		free(temp1);
		free(string);
		string = temp2;
		i++;
	}
	return (string);
}

char	*join_with_num_of_spaces(char **cmds, int *spaces, t_mini_shell *data)
{
	char	*string;

	if (data->before == 1)
	{
		data->before = 0;
		string = join_spaces_before(cmds, spaces);
		if (!string)
			return (NULL);
		return (string);
	}
	string = ft_strdup(cmds[0]);
	string = join_with_num_of_spaces2(cmds, spaces, string);
	if (!string)
		return (NULL);
	return (string);
}
