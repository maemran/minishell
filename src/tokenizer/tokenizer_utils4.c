/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:33:25 by salshaha          #+#    #+#             */
/*   Updated: 2025/04/19 03:37:21 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	initialize_here_doc(t_tokenizer *commands, int *flag, char *array)
{
	char	*temp1;
	char	*temp2;

	if (*flag == 0)
	{
		*flag = 1;
		free(commands->delimiter);
		commands->delimiter = ft_strdup(array);
		if (!commands->delimiter)
			return (FAILURE);
	}
	else
	{
		temp2 = ft_strjoin(" ", array);
		if (!temp2)
			return (FAILURE);
		temp1 = ft_strjoin(commands->delimiter, temp2);
		free(temp2);
		if (!temp1)
			return (FAILURE);
		free(commands->delimiter);
		commands->delimiter = temp1;
	}
	return (SUCCESS);
}

char	**tokenizer_checks(char *input, t_mini_shell *data)
{
	char	**split_cmd;

	if (!(multi_pipes(input)) || (input[0] == '|' && input[1] == '\0')
		|| input[0] == '|')
		data->syntax_error = 1;
	if (ft_strlen(input) > 0 && input[ft_strlen(input) - 1] == '|')
		data->pipe = 1;
	split_cmd = ft_split_cmd(input, '|');
	return (split_cmd);
}

int	tokinizer_loop2(t_tokenizer *commands)
{
	int	res;

	res = 0;
	if (commands->array[commands->i][0] == '>'
		|| (ft_strncmp(commands->array[commands->i], ">>", 3) == 0))
	{
		res = red_out_check(commands);
		if (res == 2)
			return (2);
		else if (res == 0)
			return (FAILURE);
	}
	else
	{
		res = cmd_and_args(commands);
		if (res == 0)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	tokinizer_loop(t_tokenizer *commands, t_mini_shell *data)
{
	int	res;

	res = 0;
	while (commands->array[commands->i])
	{
		if (commands->array[commands->i][0] == '<'
			|| (ft_strncmp(commands->array[commands->i], "<<", 3) == 0))
		{
			res = fill_input(commands, data);
			if (res == 2)
				return (2);
			else if (res == 0)
				return (FAILURE);
		}
		else
		{
			res = tokinizer_loop2(commands);
			if (res == 2)
				return (2);
			else if (res == 0)
				return (FAILURE);
		}
		commands->i++;
	}
	return (SUCCESS);
}
