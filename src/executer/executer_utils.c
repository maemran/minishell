/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 02:39:08 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:33:59 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	initialize_exe(t_executer *exe, t_mini_shell *data, t_tokenizer **commands)
{
	if (!exe)
		return (FAILURE);
	exe->j = 0;
	exe->i = 0;
	exe->h_i = 0;
	exe->h_j = 0;
	exe->counter = 0;
	exe->size = size_of_commands(commands);
	if (!pipes_init(exe, exe->size))
		return (FAILURE);
	if (!ft_getenv(data, "PATH"))
		exe->path = NULL;
	else
	{
		exe->path = ft_strdup(ft_getenv(data, "PATH"));
		if (!exe->path)
			return (FAILURE);
	}
	exe->command = NULL;
	exe->paths = NULL;
	exe->command_args = NULL;
	exe->fds = NULL;
	return (SUCCESS);
}

int	size_of_commands(t_tokenizer **commands)
{
	int	i;

	i = 0;
	while (commands[i])
		i++;
	return (i);
}

int	quotes_search(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	remove_quotes(char **array, t_mini_shell *data)
{
	int		i;
	char	*string;

	i = 0;
	while (array[i])
	{
		if (quotes_search(array[i]))
		{
			string = expand(array[i], data);
			if (!string)
				return (FAILURE);
			free(array[i]);
			array[i] = string;
		}
		i++;
	}
	return (SUCCESS);
}

int	free_param(t_executer *exe, char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (exe->command_args)
	{
		ft_free_tow_d_array(exe->command_args);
		exe->command_args = NULL;
	}
	if (exe->paths)
	{
		ft_free_tow_d_array(exe->paths);
		exe->paths = NULL;
	}
	return (FAILURE);
}
