/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Preparing_for_expander.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:53:14 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:33 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	sapce_inside_qouts(char *string, char c)
{
	int	i;
	int	qout;

	i = 0;
	qout = 0;
	while (string[i])
	{
		if (string[i] == c)
		{
			if (qout == 0)
				qout = 1;
			else if (qout == 1)
				qout = 0;
		}
		if (qout == 1 && string[i] == ' ')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	prepare_before_expand(t_mini_shell *data, char **str)
{
	char	*string;
	char	**array;

	array = ft_split_cmd(*str, ' ');
	if (!array)
		return (FAILURE);
	if (!expander(array, data))
	{
		ft_free_tow_d_array(array);
		return (FAILURE);
	}
	string = join_two_d_to_string(array, " ");
	if (!string)
	{
		ft_free_tow_d_array(array);
		return (FAILURE);
	}
	ft_free_tow_d_array(array);
	free(*str);
	*str = string;
	return (SUCCESS);
}

int	expand_tokenizer_loop(t_tokenizer **commands, t_mini_shell *data, int *i)
{
	if (commands[*i]->cmd != NULL && (quotes_search(commands[*i]->cmd) == 0))
	{
		if (!prepare_before_expand(data, &commands[*i]->cmd))
			return (FAILURE);
	}
	if (commands[*i]->cmd_args != NULL
		&& (quotes_search(commands[*i]->cmd_args) == 0
			&& (sapce_inside_qouts(commands[*i]->cmd_args, '\'')
				&& ft_strncmp(commands[*i]->cmd_args, "echo", 4))
			&& (sapce_inside_qouts(commands[*i]->cmd_args, '\'')
				&& ft_strncmp(commands[*i]->cmd_args, "export", 6))))
	{
		if (!prepare_before_expand(data, &commands[*i]->cmd_args))
			return (FAILURE);
	}
	if (commands[*i]->infile)
	{
		if (!prepare_before_expand(data, &commands[*i]->infile))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	expand_tokenizer(t_tokenizer **commands, t_mini_shell *data)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i])
	{
		if (!expand_tokenizer_loop(commands, data, &i))
			return (FAILURE);
		if (commands[i]->outfile)
		{
			if (!prepare_before_expand(data, &commands[i]->outfile))
				return (FAILURE);
			j = 0;
			while (commands[i]->out_files != NULL && commands[i]->out_files[j])
			{
				if (!prepare_before_expand(data, &commands[i]->out_files[j]))
					return (FAILURE);
				j++;
			}
		}
		i++;
	}
	return (SUCCESS);
}
