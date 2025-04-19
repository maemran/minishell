/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bulitin_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:14:53 by salshaha          #+#    #+#             */
/*   Updated: 2025/04/14 10:15:47 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	built_execution2(t_tokenizer *commands, t_mini_shell *data)
{
	int	null_check;

	null_check = 1;
	if (!ft_strncmp(commands->cmd, "export", 7) || !ft_strncmp(commands->cmd,
			"\"export\"", 9) || !ft_strncmp(commands->cmd, "\'export\'", 9))
		null_check = export(commands->cmd_args, data);
	else if (!ft_strncmp(commands->cmd, "echo", 5) || !ft_strncmp(commands->cmd,
			"\"echo\"", 9) || !ft_strncmp(commands->cmd, "\'echo\'", 9))
		null_check = echo(commands->cmd_args, data);
	else if (!ft_strncmp(commands->cmd, "pwd", 4) || !ft_strncmp(commands->cmd,
			"\"pwd\"", 6) || !ft_strncmp(commands->cmd, "\'pwd\'", 6))
		null_check = pwd();
	else
		null_check = built_execution3(commands, data);
	return (null_check);
}

int	execute_builtins(t_tokenizer *commands, t_mini_shell *data)
{
	int	null_check;

	null_check = 1;
	if (!ft_strncmp(commands->cmd, "cd", 3))
		null_check = cd((commands->cmd_args) + 3, data, commands->cmd_args);
	else if (!ft_strncmp(commands->cmd, "\"cd\"", 5))
		null_check = cd((commands->cmd_args) + 5, data, commands->cmd_args);
	else if (!ft_strncmp(commands->cmd, "\'cd\'", 5))
		null_check = cd((commands->cmd_args) + 5, data, commands->cmd_args);
	else if (!ft_strncmp(commands->cmd, "unset", 6)
		|| !ft_strncmp(commands->cmd, "\"unset\"", 8)
		|| !ft_strncmp(commands->cmd, "\'unset\'", 8))
		null_check = unset_string(commands->cmd_args, data);
	else if ((!ft_strncmp(commands->cmd, "export", 7)
			&& commands->cmd_args[6] == '\0') || (!ft_strncmp(commands->cmd,
				"\"export\"", 9) && commands->cmd_args[8] == '\0')
		|| (!ft_strncmp(commands->cmd, "\'export\'", 9)
			&& commands->cmd_args[8] == '\0'))
		null_check = sort_export(data);
	else
		null_check = built_execution2(commands, data);
	if (null_check == 0)
		return (FAILURE);
	return (SUCCESS);
}

void	builtins_close_fds(t_tokenizer *command, int size, t_executer *exe)
{
	close(exe->saved_stdout);
	close(exe->saved_stdin);
	if (command->fd_in != 0 && command->fd_in != -1)
		close(command->fd_in);
	if (command->fd_out != 0 && command->fd_out != -1)
		close(command->fd_out);
	if (exe->i != 0)
		close(exe->fd[exe->i - 1][0]);
	if (exe->i != (size - 1))
		close(exe->fd[exe->i][1]);
}

int	builtins_in_the_mid(t_tokenizer *commands, t_mini_shell *data)
{
	int	null_check;

	null_check = 1;
	if ((!ft_strncmp(commands->cmd, "export", 7)
			&& commands->cmd_args[6] == '\0') || (!ft_strncmp(commands->cmd,
				"\"export\"", 9) && commands->cmd_args[8] == '\0')
		|| (!ft_strncmp(commands->cmd, "\'export\'", 9)
			&& commands->cmd_args[8] == '\0'))
		null_check = sort_export(data);
	else if (!ft_strncmp(commands->cmd, "echo", 5) || !ft_strncmp(commands->cmd,
			"\"echo\"", 9) || !ft_strncmp(commands->cmd, "\'echo\'", 9))
		null_check = echo(commands->cmd_args, data);
	else if (!ft_strncmp(commands->cmd, "pwd", 4) || !ft_strncmp(commands->cmd,
			"\"pwd\"", 6) || !ft_strncmp(commands->cmd, "\'pwd\'", 6))
		null_check = pwd();
	else
		null_check = built_execution3(commands, data);
	if (null_check == 0)
		return (FAILURE);
	return (SUCCESS);
}

int	built_execution(t_tokenizer *command, t_mini_shell *data, t_executer *exe)
{
	int	num;

	exe->saved_stdout = dup(1);
	exe->saved_stdin = dup(0);
	if (!redirection(command, data, exe))
	{
		close(exe->saved_stdout);
		close(exe->saved_stdin);
		return (FAILURE);
	}
	if (exe->size == 1)
		num = execute_builtins(command, data);
	else
		num = builtins_in_the_mid(command, data);
	if (num == 0)
	{
		close(exe->saved_stdout);
		close(exe->saved_stdin);
		return (SUCCESS);
	}
	dup2(exe->saved_stdout, 1);
	dup2(exe->saved_stdin, 0);
	builtins_close_fds(command, exe->size, exe);
	return (SUCCESS);
}
