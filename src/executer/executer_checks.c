/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 02:10:45 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:33:53 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_check(t_mini_shell *data)
{
	if (data->pipe == 1)
		data->pipe = 0;
	data->syntax_error = 0;
	data->here_with_error = 0;
	error_msg("syntax error near unexpected token\n", NULL);
	data->exit_status = 2;
	return (SUCCESS);
}

int	input_file_check(t_tokenizer *command)
{
	if (access(command->infile, F_OK) != 0)
	{
		error_msg(command->infile, ": No such file or directory\n");
		return (1);
	}
	else if (access(command->infile, R_OK) != 0)
	{
		error_msg(command->infile, ": Permission denied\n");
		return (1);
	}
	return (0);
}

void	command_found_checks2(t_tokenizer *commands, t_executer *exe,
		t_mini_shell *data, t_tokenizer **cmds)
{
	error_msg(commands->cmd, ": filename argument required\n");
	free_child_process(data, cmds, exe, 2);
}

void	command_found_checks(t_tokenizer *commands, t_executer *exe,
		t_mini_shell *data, t_tokenizer **cmds)
{
	if (access(commands->cmd, F_OK) != 0 || !(ft_strncmp(commands->cmd, "..",
				3)))
		error_msg(commands->cmd, ": command not found\n");
	else if (access(commands->cmd, X_OK) != 0)
		error_msg(commands->cmd, ": Permission denied\n");
	else if (ft_strncmp(commands->cmd, "./", 2) == 0
		|| ft_strncmp(commands->cmd, "../", 3) == 0
		|| ft_strncmp(commands->cmd, "/", 1) == 0)
	{
		error_msg(commands->cmd, ": Is a directory\n");
		type_of_exit(126, data, exe, cmds);
	}
	else if (exe->counter == exe->j)
	{
		if (commands->cmd[ft_strlen(commands->cmd) - 1] == '/')
		{
			error_msg(commands->cmd, ": Is a directory\n");
			type_of_exit(126, data, exe, cmds);
		}
		error_msg(commands->cmd, ": command not found\n");
	}
	else if (ft_strncmp(commands->cmd, ".", 2) == 0)
		command_found_checks2(commands, exe, data, cmds);
}

int	check_before_executer2(t_tokenizer ***commands, t_mini_shell *data)
{
	if (data->pipe == 1)
	{
		data->pipe = 0;
		*commands = add_commands(*commands, data);
		if (!(*commands))
		{
			if (g_signum == 2)
				printf(ARR_SIG);
			return (FAILURE);
		}
	}
	else if (no_command_check(*commands))
	{
		*commands = clear_command(*commands);
		if (!(*commands))
			return (2);
		*commands = add_commands(*commands, data);
		if (!(*commands))
		{
			if (g_signum == 2)
				printf(ARR_SIG);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
