/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_before_execute_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:40:27 by salshaha          #+#    #+#             */
/*   Updated: 2025/04/19 03:33:19 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_error_for_red(t_tokenizer **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (commands[i]->infile)
		{
			if (commands[i]->infile[0] == '<' || commands[i]->infile[0] == '>')
				return (FAILURE);
		}
		if (commands[i]->outfile)
		{
			if (commands[i]->outfile[0] == '<'
				|| commands[i]->outfile[0] == '>')
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	syntax_error_check(t_tokenizer **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (commands[i]->syntax_error == 1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	close_here_doc_fds(t_executer *exe, t_tokenizer **commands)
{
	int	i;

	i = 0;
	while (i < count_num_of_here_docs(commands))
	{
		if (exe->fds[i] != -1)
			close(exe->fds[i]);
		i++;
	}
}

void	ft_close(t_tokenizer *command, t_tokenizer **commands, t_executer *exe)
{
	int	i;

	i = 0;
	if (is_here_doc(commands))
		close_here_doc_fds(exe, commands);
	if (command->fd_in != 0 && command->fd_in != -1)
		close(command->fd_in);
	if (command->fd_out != 0 && command->fd_out != -1)
		close(command->fd_out);
	while (i < (size_of_commands(commands) - 1))
	{
		close(exe->fd[i][0]);
		close(exe->fd[i][1]);
		i++;
	}
}

int	no_command_check(t_tokenizer **commands)
{
	int	flag;
	int	size;

	flag = 0;
	size = size_of_commands(commands) - 1;
	if (size == 0)
		return (FAILURE);
	if (commands[size]->infile == NULL)
		flag++;
	if (commands[size]->outfile == NULL)
		flag++;
	if (commands[size]->cmd == NULL)
		flag++;
	if (flag == 3)
		return (SUCCESS);
	return (FAILURE);
}
