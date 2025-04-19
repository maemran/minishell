/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:26:15 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:28 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*home_sign(char *split_cmd, char **string_cmd, int n,
		t_mini_shell *data)
{
	char	*var_out;
	char	*string;

	if (string_cmd[n][1] == '/' || string_cmd[n][1] == '\0')
	{
		var_out = ft_getenv(data, "HOME");
		if (!var_out)
			return (NULL);
		else
			var_out = ft_strdup(var_out);
		if (!var_out)
			return (NULL);
	}
	if (string_cmd[n][1] == '/')
	{
		string = ft_strjoin(var_out, split_cmd + 1);
		free(var_out);
		if (!string)
			return (NULL);
	}
	if (string_cmd[n][1] == '\0')
		string = var_out;
	return (string);
}

char	*expand(char *split_cmd, t_mini_shell *data)
{
	char	**cmds;
	char	*string;
	int		null_check;
	int		i;

	i = 0;
	cmds = tokens(split_cmd);
	null_check = 1;
	if (!cmds)
		return (NULL);
	while (cmds[i])
	{
		if (cmds[i][0] == '$')
			null_check = dollar_sign(cmds, i, 1, data);
		else if (cmds[i][0] == '\'')
			null_check = single_qouts(cmds[i], cmds, i);
		else if (cmds[i][0] == '"')
			null_check = double_qouts(cmds[i], cmds, i, data);
		if (!null_check)
			return ((char *)ft_exit_tokens(NULL, cmds));
		i++;
	}
	string = toknes_join(cmds);
	ft_free_tow_d_array(cmds);
	return (string);
}

int	expander(char **split_cmd, t_mini_shell *data)
{
	int		i;
	char	*string;

	i = 0;
	while (split_cmd[i])
	{
		if ((split_cmd[i][0] == '~' && split_cmd[i][1] == '\0')
			|| (split_cmd[i][0] == '~' && split_cmd[i][1] == '/'))
		{
			string = home_sign(split_cmd[i], split_cmd, i, data);
			if (!string)
				return (FAILURE);
		}
		else
		{
			string = expand(split_cmd[i], data);
			if (!string)
				return (FAILURE);
		}
		free(split_cmd[i]);
		split_cmd[i] = string;
		i++;
	}
	return (SUCCESS);
}

int	modify_input(char *input, t_mini_shell *data)
{
	t_tokenizer	**commands;

	if (!odd_num_qouts(input))
		return (SUCCESS);
	commands = tokenizer_prepration(input, data);
	if (!commands)
		return (FAILURE);
	commands = check_before_executer(commands, data);
	if (!commands && g_signum == 0)
		return (FAILURE);
	if (commands)
		free_commands(commands);
	return (SUCCESS);
}
