/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 02:25:00 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:33:31 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_parent_fds(t_executer *exe)
{
	if (exe->i != 0)
		close(exe->fd[exe->i - 1][0]);
	if (exe->i != (exe->size - 1))
		close(exe->fd[exe->i][1]);
}

int	executer_loop2(t_mini_shell *data, t_tokenizer **commands, t_executer *exe)
{
	if (!underscore(data, commands, exe))
		return (FAILURE);
	if ((size_of_commands(commands) == 1 || exe->i == (exe->size - 1))
		&& is_exit(commands[exe->i]->cmd))
	{
		if (!exit_command(commands[exe->i]->cmd_args, exe, data, commands))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	executer_loop(t_mini_shell *data, t_tokenizer **commands, t_executer *exe)
{
	exe->i = 0;
	while (commands[exe->i])
	{
		if (!executer_loop2(data, commands, exe))
			return (FAILURE);
		if (is_biltin(commands[exe->i]->cmd))
		{
			if (!built_execution(commands[exe->i], data, exe))
				return (FAILURE);
			commands[exe->i]->builtin = 1;
			exe->i++;
			continue ;
		}
		exe->id = fork();
		if (exe->id == 0)
		{
			if (!child_process(data, commands, exe))
				return (FAILURE);
		}
		if (exe->id != 0)
			close_parent_fds(exe);
		exe->i++;
	}
	return (SUCCESS);
}

void	free_child_process(t_mini_shell *data, t_tokenizer **commands,
		t_executer *exe, int status)
{
	if (commands)
		free_commands(commands);
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
	free_minishell_struct(data);
	exit(status);
}

int	child_process(t_mini_shell *data, t_tokenizer **commands, t_executer *exe)
{
	int	num;

	signal(SIGQUIT, SIG_DFL);
	num = redirection(commands[exe->i], data, exe);
	if (num == 1 || num == 0)
		ft_close(commands[exe->i], commands, exe);
	if (num == 1)
		free_child_process(data, commands, exe, 1);
	if (num == 0)
		return (FAILURE);
	if ((commands[exe->i]->infile && commands[exe->i]->outfile
			&& commands[exe->i]->cmd == NULL) || (commands[exe->i]->cmd == NULL
			&& commands[exe->i]->here_doc == 1))
	{
		ft_close(commands[exe->i], commands, exe);
		free_child_process(data, commands, exe, 0);
	}
	ft_close(commands[exe->i], commands, exe);
	num = execute(commands[exe->i], data, exe, commands);
	if (num == 0)
		return (FAILURE);
	if (num == 1)
		free_child_process(data, commands, exe, 0);
	return (SUCCESS);
}
