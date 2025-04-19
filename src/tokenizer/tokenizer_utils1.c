/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:20:13 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:37:05 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirection_check(char **array, int i)
{
	int	x;

	x = i;
	if ((array[i][0] == '<' || array[i][0] == '>') && array[i + 1] == NULL)
		return (0);
	while ((array[i][0] == '<' || array[i][0] == '>') && array[i + 1] != NULL)
		i++;
	if (array[i] == NULL || ((i - x) > 1))
		return (0);
	else if ((array[0][0] == '<' || array[0][0] == '>') && (array[1][0] == '<'
				|| array[1][0] == '>') && array[2] == NULL)
		return (0);
	return (i);
}

int	red_in_check1(t_tokenizer *commands)
{
	commands->syntax_error = 1;
	if (commands->delimiter)
	{
		commands->delimiters = ft_split_cmd(commands->delimiter, ' ');
		if (!commands->delimiters)
			return (FAILURE);
	}
	free(commands->str);
	ft_free_tow_d_array(commands->array);
	commands->array = NULL;
	commands->str = NULL;
	return (2);
}

int	red_in_check2(t_tokenizer *commands, t_mini_shell *data)
{
	int	num;

	if (ft_strncmp(commands->array[commands->i], "<<", 3) == 0)
	{
		commands->here_doc = 1;
		commands->here_red = 1;
		commands->fd_num = data->here_doc_num;
	}
	else
		commands->here_red = 0;
	num = commands->i;
	commands->i = redirection_check(commands->array, commands->i);
	free(commands->infile);
	if (commands->here_doc == 1 && !ft_strncmp(commands->array[num], "<<", 3))
	{
		if (!initialize_here_doc(commands, &(commands->flag2),
				commands->array[commands->i]))
			return (FAILURE);
	}
	commands->infile = ft_strdup(commands->array[commands->i]);
	if (!commands->infile)
		return (FAILURE);
	return (SUCCESS);
}

int	red_out_check(t_tokenizer *commands)
{
	if (redirection_check(commands->array, commands->i) == 0)
	{
		free(commands->str);
		ft_free_tow_d_array(commands->array);
		commands->array = NULL;
		commands->str = NULL;
		commands->syntax_error = 1;
		return (2);
	}
	else
	{
		if (ft_strncmp(commands->array[commands->i], ">>", 3) == 0)
			commands->append = 1;
		commands->i = redirection_check(commands->array, commands->i);
		free(commands->outfile);
		commands->outfile = ft_strdup(commands->array[commands->i]);
		if (!commands->outfile)
			return (FAILURE);
		if (!multi_out_file(commands, &(commands->flag3),
				commands->array[commands->i]))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	cmd_and_args(t_tokenizer *commands)
{
	if (commands->flag == 0)
	{
		commands->flag = 1;
		commands->cmd = ft_strdup(commands->array[commands->i]);
		if (!commands->cmd)
			return (FAILURE);
	}
	commands->temp2 = ft_strjoin(commands->array[commands->i], " ");
	if (!commands->temp2)
		return (FAILURE);
	commands->temp1 = ft_strjoin(commands->str, commands->temp2);
	if (!commands->temp1)
		return (FAILURE);
	free(commands->temp2);
	commands->temp2 = NULL;
	free(commands->str);
	commands->str = commands->temp1;
	return (SUCCESS);
}
