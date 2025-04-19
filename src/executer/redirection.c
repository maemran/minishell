/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 02:20:18 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:34:52 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipes_init(t_executer *exe, int size)
{
	int	i;

	i = 0;
	exe->fd = malloc(sizeof(int *) * (size - 1));
	if (!exe->fd)
		return (FAILURE);
	while (i < (size - 1))
	{
		exe->fd[i] = malloc(sizeof(int) * 2);
		if (!exe->fd[i])
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	free_pipes(t_executer *exe)
{
	int	i;

	i = 0;
	while (i < (exe->size) - 1)
	{
		free(exe->fd[i]);
		i++;
	}
	free(exe->fd);
	exe->fd = NULL;
}

int	redirection2(t_tokenizer *command, t_mini_shell *data, t_executer *exe)
{
	int	num;

	(void)data;
	if (command->infile && command->here_red == 0)
	{
		command->fd_in = open(command->infile, O_RDONLY);
		dup2(command->fd_in, 0);
	}
	if (command->here_red == 1)
		dup2(exe->fds[command->fd_num], 0);
	if (command->outfile)
	{
		num = open_redirection_out(command);
		if (num == 1)
			return (1);
		else if (num == 0)
			return (FAILURE);
	}
	return (3);
}

int	redirection(t_tokenizer *command, t_mini_shell *data, t_executer *exe)
{
	int	num;

	(void)data;
	if (command->infile && command->here_doc == 0)
	{
		if (input_file_check(command) == 1)
			return (1);
	}
	num = redirection2(command, data, exe);
	if (num == 0)
		return (FAILURE);
	else if (num == 1)
		return (1);
	if (command->infile == NULL && exe->i != 0)
		dup2(exe->fd[exe->i - 1][0], 0);
	if (command->outfile == NULL && exe->i != (exe->size - 1))
		dup2(exe->fd[exe->i][1], 1);
	return (3);
}
