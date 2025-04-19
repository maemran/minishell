/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:15:49 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:37:12 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_initialize_tokenizer2(t_tokenizer *commands)
{
	commands->syntax_error = 0;
	commands->here_doc = 0;
	commands->append = 0;
	commands->fd_in = 0;
	commands->fd_num = -1;
	commands->fd_out = 0;
	commands->builtin = 0;
	commands->i = 0;
	commands->flag = 0;
	commands->flag2 = 0;
	commands->flag3 = 0;
}

int	ft_initialize_tokenizer(t_tokenizer *commands)
{
	commands->cmd = NULL;
	commands->cmd_args = NULL;
	commands->delimiter = NULL;
	commands->delimiters = NULL;
	commands->out_files = NULL;
	commands->out = NULL;
	commands->temp1 = NULL;
	commands->temp2 = NULL;
	commands->array = NULL;
	commands->str = NULL;
	commands->outs = NULL;
	commands->infile = NULL;
	commands->outfile = NULL;
	ft_initialize_tokenizer2(commands);
	return (SUCCESS);
}

void	free_arrays(t_tokenizer *commands)
{
	if (commands->array)
	{
		ft_free_tow_d_array(commands->array);
		commands->array = NULL;
	}
	if (commands->temp1)
	{
		free(commands->temp1);
		commands->temp1 = NULL;
	}
	if (commands->temp2)
	{
		free(commands->temp2);
		commands->temp2 = NULL;
	}
	if (commands->str)
	{
		free(commands->str);
		commands->str = NULL;
	}
}

t_tokenizer	*free_command(t_tokenizer *commands)
{
	if (!commands)
		return (NULL);
	free_arrays(commands);
	if (commands->cmd)
		free(commands->cmd);
	if (commands->cmd_args)
		free(commands->cmd_args);
	if (commands->delimiter)
		free(commands->delimiter);
	if (commands->infile)
		free(commands->infile);
	if (commands->outfile)
		free(commands->outfile);
	if (commands->out)
		free(commands->out);
	if (commands->delimiters)
		ft_free_tow_d_array(commands->delimiters);
	if (commands->out_files)
		ft_free_tow_d_array(commands->out_files);
	if (commands->outs)
		free(commands->outs);
	if (commands)
		free(commands);
	commands = NULL;
	return (NULL);
}

int	multi_out_file(t_tokenizer *commands, int *flag, char *array)
{
	char	*temp1;
	char	*temp2;

	if (*flag == 0)
	{
		*flag = 1;
		free(commands->out);
		commands->out = ft_strdup(array);
		if (!commands->out)
			return (FAILURE);
	}
	else
	{
		temp2 = ft_strjoin(" ", array);
		if (!temp2)
			return (FAILURE);
		temp1 = ft_strjoin(commands->out, temp2);
		free(temp2);
		if (!temp1)
			return (FAILURE);
		free(commands->out);
		commands->out = temp1;
	}
	return (SUCCESS);
}
