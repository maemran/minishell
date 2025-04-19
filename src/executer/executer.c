/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran < maemran@student.42amman.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:51:30 by salshaha          #+#    #+#             */
/*   Updated: 2025/04/19 11:07:37 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute2(t_tokenizer *commands, t_mini_shell *data, t_executer *exe,
		t_tokenizer **cmds)
{
	if (access(commands->cmd, F_OK & X_OK) != 0 || exe->counter == exe->j)
	{
		if (!is_biltin(commands->cmd))
			command_found_checks(commands, exe, data, cmds);
		if (exe->i == exe->size - 1)
			free_child_process(data, cmds, exe, 127);
		else
			free_child_process(data, cmds, exe, 0);
	}
	ft_free_tow_d_array(exe->paths);
	ft_free_tow_d_array(exe->command_args);
	exe->command_args = NULL;
	exe->paths = NULL;
}

int	execute(t_tokenizer *commands, t_mini_shell *data, t_executer *exe,
		t_tokenizer **cmds)
{
	int	num;

	if (!relative_absolute_path(commands, data))
		return (FAILURE);
	if (!ft_getenv(data, "PATH"))
	{
		error_msg(commands->cmd, ": command not found\n");
		if (exe->i == exe->size - 1)
			free_child_process(data, cmds, exe, 127);
		else
			free_child_process(data, cmds, exe, 0);
	}
	if (!is_biltin(commands->cmd))
	{
		num = path_search(commands, data, exe);
		if (num == 0)
			return (FAILURE);
		else if (num == 2)
			return (SUCCESS);
	}
	execute2(commands, data, exe, cmds);
	return (SUCCESS);
}

int	executer2(t_mini_shell *data, t_tokenizer **commands, t_executer *exe)
{
	while (exe->i < (exe->size - 1))
	{
		pipe(exe->fd[exe->i]);
		exe->i++;
	}
	if (!(executer_loop(data, commands, exe)))
	{
		free_exe(exe);
		return (FAILURE);
	}
	if (is_here_doc(commands))
		close_here_doc_fds(exe, commands);
	exit_status(data, commands, exe);
	free_exe(exe);
	return (SUCCESS);
}

int	executer(t_mini_shell *data, t_tokenizer **commands)
{
	t_executer	*exe;
	int			num;

	exe = malloc(sizeof(t_executer));
	if (!initialize_exe(exe, data, commands))
	{
		free(exe);
		return (FAILURE);
	}
	if (is_here_doc(commands))
	{
		num = prepare_here_doc(data, commands, exe);
		if (num == 2)
			return (2);
		else if (num == 0)
			return (FAILURE);
	}
	if (!executer2(data, commands, exe))
		return (FAILURE);
	if (!export_underscore(data))
		return (FAILURE);
	return (SUCCESS);
}

t_tokenizer	**check_before_executer(t_tokenizer **commands, t_mini_shell *data)
{
	int	num;

	if (!syntax_error_check(commands) || data->syntax_error == 1
		|| !syntax_error_for_red(commands))
	{
		if (!error_check(data))
			return (exit_executer(commands));
		return (commands);
	}
	else
	{
		num = check_before_executer2(&commands, data);
		if (num == 0)
			return (NULL);
		else if (num == 2)
			return (exit_executer(commands));
	}
	num = executer(data, commands);
	if (num == 0)
		return (exit_executer(commands));
	else if (num == 2)
		return (commands);
	return (commands);
}
