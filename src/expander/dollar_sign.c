/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:22:56 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:17 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	dollar_sign3(int type, t_mini_shell *data, t_expander *expander)
{
	int	flag;

	flag = 0;
	if (expander->split_pos[0][ft_strlen(expander->split_pos[0]) - 1] == '"')
	{
		expander->split_pos[0][ft_strlen(expander->split_pos[0]) - 1] = '\0';
		flag = 1;
	}
	if (!(fill_dollar_sign(expander->split_pos, type, data)))
		return (FAILURE);
	if (flag == 1)
	{
		expander->temp = ft_strjoin(expander->split_pos[0], "\"");
		if (!expander->temp)
			return (FAILURE);
		free(expander->split_pos[0]);
		expander->split_pos[0] = expander->temp;
	}
	return (SUCCESS);
}

t_expander	*dollar_sign2(char *split_cmd, int type, t_mini_shell *data)
{
	t_expander	*expander;

	expander = malloc(sizeof(t_expander));
	if (!expander)
		return (NULL);
	ft_initialize_expander(expander);
	expander->pos = ft_strchr(split_cmd, '$');
	expander->pre_string = ft_pre_string(split_cmd, expander->pos);
	if (!expander->pre_string)
		return (free_struct(expander));
	expander->split_pos = ft_split_cmd(expander->pos, ' ');
	if (!expander->split_pos)
		return (free_struct(expander));
	if (!dollar_sign3(type, data, expander))
		return (free_struct(expander));
	expander->last_string = collect_string(expander);
	if (!expander->last_string)
		return (free_struct(expander));
	return (expander);
}

char	*dollar_sign_check(char **cmds, int n)
{
	char	*split_cmd;

	split_cmd = ft_strdup(cmds[n]);
	if (!split_cmd)
		return (NULL);
	if (ft_strncmp("$\"", split_cmd, 3) == 0)
	{
		free(cmds[n]);
		cmds[n] = ft_strdup("$");
		free(split_cmd);
		if (!cmds[n])
			return (NULL);
		return ("2");
	}
	if (split_cmd[0] == '$' && split_cmd[1] == '\'')
	{
		if (!single_qouts(split_cmd + 1, cmds, n))
		{
			free(split_cmd);
			return (NULL);
		}
		return ("2");
	}
	return (split_cmd);
}

char	*dollar_sign_check2(char **cmds, int n, t_mini_shell *data)
{
	char	*split_cmd;

	split_cmd = dollar_sign_check(cmds, n);
	if (split_cmd == NULL)
		return (FAILURE);
	if (split_cmd[0] == '2')
		return ("2");
	if (split_cmd[0] == '$' && split_cmd[1] == '\"')
	{
		if (!(double_qouts(split_cmd + 1, cmds, n, data)))
			return (NULL);
		free(split_cmd);
		return ("2");
	}
	return (split_cmd);
}

int	dollar_sign(char **cmds, int n, int type, t_mini_shell *data)
{
	t_expander	*expander;
	char		*split_cmd;

	split_cmd = dollar_sign_check2(cmds, n, data);
	if (split_cmd == NULL)
		return (FAILURE);
	if (split_cmd[0] == '2')
		return (SUCCESS);
	expander = dollar_sign2(split_cmd, type, data);
	free(split_cmd);
	if (!expander)
		return (ft_exit_expander(expander, NULL));
	free(cmds[n]);
	cmds[n] = ft_strdup(expander->last_string);
	if (!cmds[n])
		return (ft_exit_expander(expander, NULL));
	free(expander->last_string);
	expander->last_string = NULL;
	free(expander);
	return (SUCCESS);
}
