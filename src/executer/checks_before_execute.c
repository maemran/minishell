/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_before_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:53:23 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:33:25 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (FAILURE);
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (SUCCESS);
	return (FAILURE);
}

int	open_fd(t_tokenizer *command, int i)
{
	int	fd;

	if (command->outs[i] == 1)
		fd = open(command->out_files[i],
				O_WRONLY | O_APPEND | O_CREAT, 0666);
	else
		fd = open(command->out_files[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

int	fd_check(void)
{
	error_msg("No such file or directory\n", NULL);
	return (FAILURE);
}

int	open_redirection_out(t_tokenizer *command)
{
	int	i;
	int	fd;

	i = 0;
	while (command->out_files[i])
	{
		if ((access(command->out_files[i], W_OK) != 0
				&& (access(command->out_files[i], F_OK) == 0))
			|| is_directory(command->out_files[i])
			|| ft_strchr(command->out_files[i], '/'))
		{
			error_msg(command->out_files[i], ": Permission denied\n");
			return (1);
		}
		if (command->out_files[i + 1] == NULL)
			break ;
		fd = open_fd(command, i);
		if (fd == -1)
			return (fd_check());
		close(fd);
		i++;
	}
	command->fd_out = open_fd(command, i);
	dup2(command->fd_out, 1);
	return (3);
}

int	paths_and_args(t_tokenizer *commands, t_executer *exe)
{
	if (!commands->cmd_args)
		return (2);
	if (commands->cmd_args != NULL)
	{
		exe->command_args = ft_split_cmd(commands->cmd_args, ' ');
		if (!exe->command_args)
			return (FAILURE);
	}
	exe->paths = ft_split(exe->path, ':');
	if (!exe->paths)
		return (free_param(exe, NULL));
	return (SUCCESS);
}
