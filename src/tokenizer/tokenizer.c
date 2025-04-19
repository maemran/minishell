/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:15:22 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:37:26 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	fill_outfiles_ands_delimiters(t_tokenizer *commands, t_mini_shell *data)
{
	if (commands->here_doc == 1)
	{
		data->here_doc_num++;
		commands->delimiters = ft_split_cmd(commands->delimiter, ' ');
		if (!commands->delimiters)
			return (FAILURE);
	}
	if (commands->outfile)
	{
		commands->out_files = ft_split_cmd(commands->out, ' ');
		if (!commands->out_files)
			return (FAILURE);
	}
	if (commands->str[0] != '\0')
	{
		commands->str[ft_strlen(commands->str) - 1] = '\0';
		commands->cmd_args = ft_strdup(commands->str);
		if (!commands->cmd_args)
			return (FAILURE);
	}
	if (commands->str[0] == '\0')
		free(commands->str);
	commands->str = NULL;
	free_arrays(commands);
	return (SUCCESS);
}

int	outs_num(char **array)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], ">>", 3) == 0)
			count++;
		else if (ft_strncmp(array[i], ">", 2) == 0)
			count++;
		i++;
	}
	return (count);
}

void	fill_outs_type(t_tokenizer *commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (commands->array[i])
	{
		if (ft_strncmp(commands->array[i], ">>", 3) == 0)
		{
			commands->outs[j] = 1;
			j++;
		}
		else if (ft_strncmp(commands->array[i], ">", 2) == 0)
		{
			commands->outs[j] = 0;
			j++;
		}
		i++;
	}
	commands->outs[j] = -1;
}

t_tokenizer	*ft_tokenizer(char *string, t_mini_shell *data)
{
	t_tokenizer	*commands;
	int			res;

	commands = malloc(sizeof(t_tokenizer));
	if (!commands)
		return (NULL);
	commands->here_red = 0;
	ft_initialize_tokenizer(commands);
	commands->array = tokens_for_tokenizer(string);
	if (!commands->array)
		return (free_command(commands));
	commands->outs = malloc(sizeof(int) * (outs_num(commands->array) + 1));
	fill_outs_type(commands);
	commands->str = ft_strdup("");
	if (!commands->str)
		return (free_command(commands));
	res = tokinizer_loop(commands, data);
	if (res == 2)
		return (commands);
	else if (res == 0)
		return (free_command(commands));
	if (!fill_outfiles_ands_delimiters(commands, data))
		return (free_command(commands));
	return (commands);
}

t_tokenizer	**tokenizer_prepration(char *input, t_mini_shell *data)
{
	t_tokenizer	**commands;
	char		**split_cmd;
	int			i;

	i = 0;
	split_cmd = tokenizer_checks(input, data);
	if (!split_cmd)
		return (NULL);
	commands = malloc(sizeof(t_tokenizer *) * (ft_two_d_len(split_cmd) + 1));
	if (!commands)
		return (free_tokenizer(NULL, split_cmd));
	while (split_cmd[i])
	{
		commands[i] = ft_tokenizer(split_cmd[i], data);
		if (!commands[i])
			return (free_tokenizer(commands, split_cmd));
		i++;
	}
	commands[i] = NULL;
	if (!expand_tokenizer(commands, data))
		return (free_tokenizer(commands, split_cmd));
	ft_free_tow_d_array(split_cmd);
	return (commands);
}
