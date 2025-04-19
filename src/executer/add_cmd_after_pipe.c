/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_after_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:41:11 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:33:14 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokenizer	**join_commands(t_tokenizer **commands, t_tokenizer **new_commands)
{
	t_tokenizer	**new;
	int			i;

	i = 0;
	if (!commands || !new_commands)
		return (NULL);
	new = malloc(sizeof(t_tokenizer *)
			* (size_of_commands(commands)
				+ size_of_commands(new_commands) + 1));
	while (commands[i])
	{
		new[i] = dup_commands(commands[i]);
		if (!new[i])
			return (exit_commands(new, NULL));
		i++;
	}
	if (!join_commands_loop(&i, new, new_commands))
		return (exit_commands(new, NULL));
	return (new);
}

int	dup_commands_check1(t_tokenizer *command, t_tokenizer *new)
{
	if (command->cmd)
	{
		new->cmd = ft_strdup(command->cmd);
		if (!new->cmd)
			return (FAILURE);
	}
	if (command->cmd_args)
	{
		new->cmd_args = ft_strdup(command->cmd_args);
		if (!new->cmd_args)
			return (FAILURE);
	}
	if (command->delimiter)
	{
		new->delimiter = ft_strdup(command->delimiter);
		if (!new->delimiter)
			return (FAILURE);
	}
	if (command->delimiters)
	{
		new->delimiters = ft_strdup_two_d(command->delimiters);
		if (!new->delimiters)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	dup_commands_check2(t_tokenizer *command, t_tokenizer *new)
{
	if (command->infile)
	{
		new->infile = ft_strdup(command->infile);
		if (!new->infile)
			return (FAILURE);
	}
	if (command->outfile)
	{
		new->outfile = ft_strdup(command->outfile);
		if (!new->outfile)
			return (FAILURE);
	}
	if (command->out_files)
	{
		new->out_files = ft_strdup_two_d(command->out_files);
		if (!new->out_files)
			return (FAILURE);
	}
	if (command->out)
	{
		new->out = ft_strdup(command->out);
		if (!new->out)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_tokenizer	*dup_commands(t_tokenizer *command)
{
	t_tokenizer	*new;

	new = malloc(sizeof(t_tokenizer));
	if (!new)
		return (NULL);
	if (!ft_initialize_tokenizer(new))
	{
		free(new);
		return (NULL);
	}
	new->append = command->append;
	if (!dup_commands_check1(command, new))
		return (NULL);
	new->fd_in = command->fd_in;
	new->fd_out = command->fd_out;
	new->here_doc = command->here_doc;
	new->here_red = command->here_red;
	new->fd_num = command->fd_num;
	if (!dup_commands_check2(command, new))
		return (NULL);
	new->syntax_error = command->syntax_error;
	return (new);
}
