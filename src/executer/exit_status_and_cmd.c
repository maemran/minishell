/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_and_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 02:30:20 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:34:25 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokenizer	**exit_executer(t_tokenizer **commmands)
{
	if (commmands)
		free_commands(commmands);
	return (NULL);
}

void	exit_status(t_mini_shell *data, t_tokenizer **commands, t_executer *exe)
{
	int	status;
	int	exit_status;

	status = 0;
	exe->i = 0;
	while (exe->i < exe->size)
	{
		wait(&status);
		if ((status & 0x7F) == SIGQUIT)
		{
			data->exit_status = 131;
			ft_putstr_fd("Quit (core dumped)\n", 2);
		}
		exit_status = (status >> 8);
		if (data->exit_status != 131 && commands[exe->i]->builtin == 0)
			data->exit_status = exit_status;
		if (data->saved_exit != 0)
		{
			data->exit_status = data->saved_exit;
			data->saved_exit = 0;
		}
		exe->i++;
	}
}

void	type_of_exit(int exit_status, t_mini_shell *data, t_executer *exe,
		t_tokenizer **cmds)
{
	if (exe->i == exe->size - 1)
		free_child_process(data, cmds, exe, exit_status);
	else
		free_child_process(data, cmds, exe, 0);
}

int	exit_command2(char **args, t_executer *exe, t_mini_shell *data,
		t_tokenizer **commands)
{
	if (!args[1])
	{
		ft_free_tow_d_array(args);
		if (exe->size == 1)
			free_child_process(data, commands, exe, data->save_exit_status);
		data->saved_exit = 0;
		return (SUCCESS);
	}
	if (!ft_atoi_ll(args[1], &(exe->code)))
	{
		error_msg("numeric argument required\n", NULL);
		ft_free_tow_d_array(args);
		data->saved_exit = 2;
		if (exe->size == 1)
			free_child_process(data, commands, exe, 2);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	exit_command(char *str, t_executer *exe, t_mini_shell *data,
		t_tokenizer **commands)
{
	char	**args;

	if (exe->size == 1)
		printf("exit\n");
	args = ft_split_cmd(str, ' ');
	if (!args)
		return (FAILURE);
	if (exit_command2(args, exe, data, commands))
		return (SUCCESS);
	if (ft_two_d_len(args) > 2)
	{
		error_msg("exit:", "too many arguments\n");
		ft_free_tow_d_array(args);
		data->saved_exit = 1;
		return (SUCCESS);
	}
	ft_free_tow_d_array(args);
	if (exe->size == 1)
		free_child_process(data, commands, exe, (exe->code) % 256);
	data->saved_exit = (exe->code) % 256;
	return (SUCCESS);
}
