/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:26:45 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:37:17 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	fill_input(t_tokenizer *commands, t_mini_shell *data)
{
	int	res;

	if (redirection_check(commands->array, commands->i) == 0)
	{
		res = red_in_check1(commands);
		if (res == 2)
			return (2);
		else if (res == 0)
			return (FAILURE);
	}
	else
	{
		if (!red_in_check2(commands, data))
			return (FAILURE);
	}
	return (SUCCESS);
}

t_tokenizer	**free_tokenizer(t_tokenizer **commands, char **split)
{
	if (split)
	{
		ft_free_tow_d_array(split);
		split = NULL;
	}
	if (commands)
	{
		free_commands(commands);
		commands = NULL;
	}
	return (NULL);
}

int	pipe_between_spaces(char *input)
{
	int	i;

	i = 0;
	if (input[0] != ' ')
		return (SUCCESS);
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (FAILURE);
	return (SUCCESS);
}

int	multi_pipes_loops(int *i, char *input)
{
	int	len;

	*i = *i + 1;
	len = ft_strlen(input);
	while (*i < len && input[*i] == ' ')
	{
		if (((*i) + 1 < len) && input[(*i) + 1] == '|')
			return (FAILURE);
		(*i)++;
	}
	return (SUCCESS);
}

int	multi_pipes(char *input)
{
	int	i;
	int	len;

	len = ft_strlen(input);
	i = 0;
	if (!pipe_between_spaces(input))
		return (FAILURE);
	while (i < len)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i = find_qouts((const char *)input, i - 1, i);
			if (i >= len)
				break ;
		}
		if (input[i] == '|' && (i + 1 < len) && input[i + 1] == '|')
			return (FAILURE);
		if (input[i] == '|' && (i + 1 < len) && input[i + 1] == ' ')
		{
			if (!multi_pipes_loops(&(i), input))
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
