/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_prepration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 02:15:52 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:34:35 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**delimiters(t_tokenizer **commands, t_mini_shell *data)
{
	int		i;
	int		j;
	int		k;
	char	**str;

	str = malloc(sizeof(char *) * (num_of_delimiters(commands, data) + 1));
	i = 0;
	k = 0;
	while (commands[i])
	{
		if (commands[i]->delimiters)
		{
			j = 0;
			while (commands[i]->delimiters[j])
			{
				str[k] = ft_strdup(commands[i]->delimiters[j]);
				k++;
				j++;
			}
		}
		i++;
	}
	str[k] = NULL;
	return (str);
}

int	num_of_delimiters(t_tokenizer **commands, t_mini_shell *data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (commands[i])
	{
		if (commands[i]->delimiters)
		{
			j = 0;
			while (commands[i]->delimiters[j])
			{
				count++;
				j++;
			}
			data->delimiter_num = i;
		}
		i++;
	}
	return (count);
}

int	count_num_of_here_docs(t_tokenizer **commands)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (commands[i])
	{
		if (commands[i]->here_doc == 1)
			count++;
		i++;
	}
	return (count);
}

int	is_here_doc(t_tokenizer **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i]->here_doc == 1)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	init_fds(t_executer *exe, t_tokenizer **commands)
{
	int	i;

	i = 0;
	while (i < count_num_of_here_docs(commands))
	{
		exe->fds[i] = -1;
		i++;
	}
	return (SUCCESS);
}
