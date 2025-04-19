/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_qouts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:11:54 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:23 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	double_qouts_loop(char **cmds, t_mini_shell *data)
{
	int	null_check;
	int	i;

	i = 0;
	null_check = 1;
	while (cmds[i])
	{
		if (cmds[i][0] == '\'' && cmds[i][1] == '\0')
			break ;
		if (cmds[i][0] == '\'')
			null_check = dollar_inside_single(cmds, i, data);
		else if (cmds[i][0] == '$' && cmds[i][1] == '\'')
			null_check = dollar_with_single(cmds, i, data);
		else if (cmds[i][0] == '$')
			null_check = dollar_sign(cmds, i, 0, data);
		if (!null_check)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

char	*double_qouts_expand(char *split_cmd, t_mini_shell *data)
{
	char	**cmds;
	char	*string;

	cmds = tokens(split_cmd);
	if (!cmds)
		return (NULL);
	if (!double_qouts_loop(cmds, data))
	{
		ft_free_tow_d_array(cmds);
		return (NULL);
	}
	string = toknes_join(cmds);
	ft_free_tow_d_array(cmds);
	return (string);
}

char	*double_qouts2(char *split_cmd, int *space, char **split_input,
		t_mini_shell *data)
{
	char	*string;
	int		i;

	i = 0;
	while (split_input[i])
	{
		string = double_qouts_expand(split_input[i], data);
		if (!string)
			return (NULL);
		free(split_input[i]);
		split_input[i] = string;
		i++;
	}
	if (is_space(split_cmd))
		string = join_with_num_of_spaces(split_input, space, data);
	else
		string = join_two_d_to_string(split_input, " ");
	if (!string)
		return (NULL);
	if (space)
		free(space);
	ft_free_tow_d_array(split_input);
	if (string[ft_strlen(string) - 1] == '"')
		string[ft_strlen(string) - 1] = '\0';
	return (string);
}

int	double_qouts_check(char *split_cmd, char **string_cmd, int n)
{
	if ((split_cmd[0] == '"' && split_cmd[1] == '\0') || (split_cmd[0] == '"'
			&& split_cmd[ft_strlen(split_cmd) - 1] != '"'))
	{
		free(string_cmd[n]);
		string_cmd[n] = ft_strdup("");
		if (!string_cmd[n])
			return (FAILURE);
		return (2);
	}
	return (SUCCESS);
}

int	double_qouts(char *split_cmd, char **string_cmd, int n, t_mini_shell *data)
{
	char	**split_input;
	char	*string;
	int		*space;

	space = NULL;
	if (double_qouts_check(split_cmd, string_cmd, n) == 2)
		return (SUCCESS);
	else if (double_qouts_check(split_cmd, string_cmd, n) == FAILURE)
		return (FAILURE);
	if (is_space(split_cmd))
	{
		space = spaces(split_cmd, data);
		if (!space)
			return (FAILURE);
	}
	split_input = ft_split_cmd(split_cmd + 1, ' ');
	if (!split_input)
		return (ft_exit_double_qouts(NULL, space));
	string = double_qouts2(split_cmd, space, split_input, data);
	if (!string)
		return (ft_exit_double_qouts(split_input, space));
	free(string_cmd[n]);
	string_cmd[n] = string;
	return (SUCCESS);
}
