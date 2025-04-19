/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bulitin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:57:07 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:33:47 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_exit(char *str)
{
	if (ft_strncmp(str, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(str, "\"exit\"", 7) == 0)
		return (1);
	if (ft_strncmp(str, "\'exit\'", 7) == 0)
		return (1);
	return (0);
}

void	print_error_msg(char *cmd, t_mini_shell *data)
{
	if (!ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "\"env\"", 6)
		|| !ft_strncmp(cmd, "\'env\'", 6))
	{
		error_msg("env: ", "No such file or directory\n");
		data->exit_status = 127;
	}
}

int	is_builtin_qouts(char *cmd)
{
	if (ft_strncmp(cmd, "\"env\"", 6) == 0 || ft_strncmp(cmd, "\'env\'",
			6) == 0)
		return (1);
	if (ft_strncmp(cmd, "\"echo\"", 9) == 0 || ft_strncmp(cmd, "\'echo\'",
			9) == 0)
		return (1);
	if (ft_strncmp(cmd, "\"export\"", 9) == 0 || ft_strncmp(cmd, "\'export\'",
			9) == 0)
		return (1);
	if (ft_strncmp(cmd, "\"unset\"", 8) == 0 || ft_strncmp(cmd, "\'unset\'",
			8) == 0)
		return (1);
	if (ft_strncmp(cmd, "\"cd\"", 5) == 0 || ft_strncmp(cmd, "\'cd\'", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "\"pwd\"", 6) == 0 || ft_strncmp(cmd, "\'pwd\'",
			6) == 0)
		return (1);
	if (ft_strncmp(cmd, "\"exit\"", 7) == 0 || ft_strncmp(cmd, "\'exit\'",
			7) == 0)
		return (1);
	return (0);
}

int	is_biltin(char *cmd)
{
	if (cmd == NULL)
		return (FAILURE);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (is_builtin_qouts(cmd))
		return (1);
	return (0);
}

int	built_execution3(t_tokenizer *commands, t_mini_shell *data)
{
	int	null_check;

	null_check = 1;
	if ((!ft_strncmp(commands->cmd, "env", 4) && commands->cmd_args[3] == '\0')
		|| (!ft_strncmp(commands->cmd, "\"env\"", 6)
			&& commands->cmd_args[5] == '\0') || (!ft_strncmp(commands->cmd,
				"\'env\'", 6) && commands->cmd_args[5] == '\0'))
		env(data);
	else
		print_error_msg(commands->cmd, data);
	return (null_check);
}
