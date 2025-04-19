/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 02:35:11 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:33:08 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	relative_absolute_path(t_tokenizer *commands, t_mini_shell *data)
{
	char	**command_args;

	if (!commands->cmd)
		return (SUCCESS);
	if (access(commands->cmd, F_OK & X_OK) == 0)
	{
		command_args = ft_split_cmd(commands->cmd_args, ' ');
		if (!command_args)
			return (FAILURE);
		if (!remove_quotes(command_args, data))
		{
			ft_free_tow_d_array(command_args);
			return (FAILURE);
		}
		execve(commands->cmd, command_args, data->env);
		ft_free_tow_d_array(command_args);
	}
	return (SUCCESS);
}

int	path_search(t_tokenizer *commands, t_mini_shell *data, t_executer *exe)
{
	char	*str;
	int		num;

	num = paths_and_args(commands, exe);
	if (num == 0)
		return (FAILURE);
	else if (num == 2)
		return (2);
	if (!remove_quotes(exe->command_args, data))
		return (free_param(exe, NULL));
	while (exe->paths[exe->j])
	{
		str = ft_strjoin("/", exe->command_args[0]);
		exe->command = ft_strjoin(exe->paths[exe->j], str);
		free(str);
		if (!exe->command)
			return (free_param(exe, NULL));
		exe->x = execve(exe->command, exe->command_args, data->env);
		if (exe->x == -1)
			exe->counter++;
		free(exe->command);
		exe->command = NULL;
		exe->j++;
	}
	return (SUCCESS);
}

int	export_underscore(t_mini_shell *data)
{
	char	*str;

	if (!unset("_", data))
		return (FAILURE);
	if (!data->underscore)
		return (SUCCESS);
	str = ft_strjoin("_=", data->underscore);
	if (!str)
		return (FAILURE);
	if (!export_string(str, data))
	{
		free(str);
		return (FAILURE);
	}
	free(str);
	return (SUCCESS);
}

int	underscore(t_mini_shell *data, t_tokenizer **commands, t_executer *exe)
{
	if ((is_space(commands[exe->i]->cmd_args)
			&& (ft_strncmp(commands[exe->i]->cmd_args, "echo $_", 7) != 0))
		&& exe->size == 1)
	{
		free(data->underscore);
		data->underscore = ft_strdup(ft_strrchr(commands[exe->i]->cmd_args, ' ')
				+ 1);
		if (data->underscore[0] == '\'')
		{
			free(data->underscore);
			data->underscore = ft_strdup(commands[exe->i]->cmd_args);
		}
	}
	else if ((ft_strncmp(commands[exe->i]->cmd_args, "echo $_", 7) != 0
			|| ft_getenv(data, "_") == NULL) && exe->size == 1)
	{
		free(data->underscore);
		data->underscore = ft_strdup(commands[exe->i]->cmd);
	}
	if (ft_strncmp(commands[exe->i]->cmd, "env", 4) == 0)
	{
		if (!export_underscore(data))
			return (FAILURE);
	}
	return (SUCCESS);
}

void	free_exe(t_executer *exe)
{
	if (exe->fds)
		free(exe->fds);
	if (exe->fd)
		free_pipes(exe);
	if (exe->command_args)
		ft_free_tow_d_array(exe->command_args);
	if (exe->paths)
		ft_free_tow_d_array(exe->paths);
	if (exe->path)
		free(exe->path);
	if (exe->command)
		free(exe->command);
	free(exe);
}
