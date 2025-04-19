/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:53:02 by salshaha          #+#    #+#             */
/*   Updated: 2025/04/19 03:34:41 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	here_doc_delimiters(char **delimiters, t_mini_shell *data, t_executer *exe,
		t_tokenizer **commands)
{
	int	i;

	i = 0;
	exe->h_i = 0;
	exe->h_j = 0;
	exe->h_k = 0;
	while (delimiters[i])
	{
		if (!(here_doc(data, delimiters[i])))
			return (FAILURE);
		fill_fds(commands, exe, data);
		i++;
	}
	unlink("buffer.txt");
	return (SUCCESS);
}

void	fill_fds(t_tokenizer **commands, t_executer *exe, t_mini_shell *data)
{
	while (commands[exe->h_i] && commands[exe->h_i]->here_doc != 1)
		(exe->h_i)++;
	while (commands[exe->h_i] && commands[exe->h_i]->delimiters[exe->h_j])
	{
		if (commands[exe->h_i]->delimiters[(exe->h_j) + 1] == NULL)
		{
			exe->fds[exe->h_k] = data->here_doc_file;
			(exe->h_i)++;
			exe->h_j = 0;
			while (commands[exe->h_i] && commands[exe->h_i]->here_doc != 1)
				(exe->h_i)++;
			exe->h_k++;
			return ;
		}
		else
		{
			close(data->here_doc_file);
			(exe->h_j)++;
			return ;
		}
	}
}

int	delmiters_comp(char *delimiter, char *buffer)
{
	if (str_comp(delimiter, buffer) == 1)
		return (SUCCESS);
	return (FAILURE);
}

char	*here_doc_exit(char *str, char **array, int *spaces)
{
	if (spaces)
		free(spaces);
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (array)
	{
		ft_free_tow_d_array(array);
		array = NULL;
	}
	return (NULL);
}

int	prepare_here_doc(t_mini_shell *data, t_tokenizer **commands,
		t_executer *exe)
{
	char	**delim;

	delim = delimiters(commands, data);
	if (!delim)
		return (FAILURE);
	exe->fds = malloc(sizeof(int) * count_num_of_here_docs(commands));
	if (!exe->fds)
		return (FAILURE);
	init_fds(exe, commands);
	if (!here_doc_delimiters(delim, data, exe, commands))
	{
		close_here_doc_fds(exe, commands);
		ft_free_tow_d_array(delim);
		free_exe(exe);
		ft_putstr_fd(SIG, 1);
		return (2);
	}
	exe->h_i = 0;
	ft_free_tow_d_array(delim);
	return (SUCCESS);
}
