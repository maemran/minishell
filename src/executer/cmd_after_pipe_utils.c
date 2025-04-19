/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_after_pipe_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:44:38 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:33:35 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokenizer	**exit_commands(t_tokenizer **cmds1, t_tokenizer **cmds2)
{
	if (cmds1)
		free_commands(cmds1);
	if (cmds2)
		free_commands(cmds2);
	return (NULL);
}

t_tokenizer	**clear_command(t_tokenizer **commands)
{
	t_tokenizer	**new;
	int			size;
	int			i;
	int			j;

	i = 0;
	j = 0;
	size = size_of_commands(commands);
	new = malloc(sizeof(t_tokenizer *) * size);
	if (!new)
		return (NULL);
	while (commands[i])
	{
		if (i != (size - 1))
		{
			new[j] = dup_commands(commands[i]);
			if (!new[j])
				return (exit_commands(new, NULL));
			j++;
		}
		i++;
	}
	new[j] = NULL;
	free_commands(commands);
	return (new);
}

t_tokenizer	**add_commands(t_tokenizer **commands, t_mini_shell *data)
{
	char		*buffer;
	t_tokenizer	**new_commands;
	t_tokenizer	**new;

	disable_ctrl_backslash();
	ft_putstr_fd(ARROW, 1);
	buffer = get_next_line(0);
	if (!buffer)
	{
		if (g_signum == 0)
			ft_putstr_fd(UNEXEOF, 2);
		restore_ctrl_backslash();
		free_commands(commands);
		return (NULL);
	}
	buffer[ft_strlen(buffer) - 1] = '\0';
	restore_ctrl_backslash();
	new_commands = tokenizer_prepration(buffer, data);
	free(buffer);
	new = join_commands(commands, new_commands);
	free_commands(new_commands);
	free_commands(commands);
	commands = NULL;
	return (new);
}

void	free_commands(t_tokenizer **commands)
{
	int	i;

	i = 0;
	if (!commands)
		return ;
	while (commands[i])
	{
		free(commands[i]->cmd);
		free(commands[i]->cmd_args);
		free(commands[i]->delimiter);
		free(commands[i]->infile);
		free(commands[i]->outfile);
		free(commands[i]->out);
		if (commands[i]->outs)
			free(commands[i]->outs);
		if (commands[i]->delimiters)
			ft_free_tow_d_array(commands[i]->delimiters);
		if (commands[i]->out_files)
			ft_free_tow_d_array(commands[i]->out_files);
		free(commands[i]);
		i++;
	}
	free(commands);
}

int	join_commands_loop(int *i, t_tokenizer **new, t_tokenizer **new_commands)
{
	int		j;

	j = 0;
	while (new_commands[j])
	{
		new[(*i) + j] = dup_commands(new_commands[j]);
		if (!new[(*i) + j])
			return (FAILURE);
		j++;
	}
	new[(*i) + j] = NULL;
	return (SUCCESS);
}
