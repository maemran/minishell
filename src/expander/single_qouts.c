/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_qouts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:22:28 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:48 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	single_qouts_check2(t_expander *expander)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (expander->pre_string[i])
	{
		if (expander->pre_string[i] == '"')
			flag = 1;
		i++;
	}
	i = 1;
	expander->pos = ft_strrchr(expander->pos, '\'');
	while (expander->pos[i])
	{
		if (expander->pos[i] == '"')
			flag = 2;
		i++;
	}
	return (flag);
}

int	single_qouts_check(char *split_cmd)
{
	t_expander	*expander;
	int			flag;
	int			offset;

	flag = 0;
	expander = malloc(sizeof(t_expander));
	if (!expander)
		return (2);
	expander->pos = ft_strchr(split_cmd, '\'');
	offset = expander->pos - split_cmd;
	expander->pre_string = malloc(offset + 1);
	if (!expander->pre_string)
	{
		free(expander);
		return (2);
	}
	expander->pre_string = ft_strncpy(expander->pre_string, split_cmd, offset);
	expander->pre_string[offset] = '\0';
	flag = single_qouts_check2(expander);
	free(expander->pre_string);
	expander->pre_string = NULL;
	free(expander);
	if (flag == 2 || flag == 1)
		return (0);
	return (1);
}

int	single_qouts2(char *split_cmd, char **string_cmd, int n,
		t_expander *expander)
{
	char	*temp;

	expander->pos = ft_strchr(split_cmd, '\'');
	expander->pre_string = ft_pre_string(split_cmd, expander->pos);
	if (!expander->pre_string)
		return (FAILURE);
	expander->split_pos = ft_split_cmd(expander->pos, ' ');
	if (!expander->split_pos)
		return (FAILURE);
	temp = ft_strtrim(expander->split_pos[0], "'");
	expander->temp = ft_strdup(temp);
	free(temp);
	if (!expander->temp)
		return (FAILURE);
	free(expander->split_pos[0]);
	expander->split_pos[0] = expander->temp;
	expander->last_string = collect_string(expander);
	if (!expander->last_string)
		return (FAILURE);
	free(string_cmd[n]);
	string_cmd[n] = expander->last_string;
	return (SUCCESS);
}

int	single_qouts(char *split_cmd, char **string_cmd, int n)
{
	t_expander	*expander;

	if (single_qouts_check(split_cmd) == 0)
		return (SUCCESS);
	else if (single_qouts_check(split_cmd) == 2)
		return (FAILURE);
	if ((split_cmd[0] == '\'' && split_cmd[1] == '\0') || (split_cmd[0] == '\''
			&& split_cmd[ft_strlen(split_cmd) - 1] != '\''))
	{
		string_cmd[n] = ft_strdup("");
		if (!string_cmd[n])
			return (FAILURE);
		return (SUCCESS);
	}
	expander = malloc(sizeof(t_expander));
	if (!expander)
		return (FAILURE);
	ft_initialize_expander(expander);
	if (!single_qouts2(split_cmd, string_cmd, n, expander))
		return (ft_exit_expander(expander, NULL));
	free(expander);
	return (SUCCESS);
}

int	odd_num_qouts(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = find_qouts(input, i - 1, i);
			if (j == i)
			{
				error_msg("Error\n", NULL);
				return (FAILURE);
			}
			else
				i = j;
		}
		i++;
	}
	return (SUCCESS);
}
