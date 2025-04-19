/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:01:57 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:08 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*num_after_dollar_sign(char *str)
{
	char	*string;

	if (str[1] == '0')
	{
		if (str[2] != '\0')
			string = ft_strjoin("./minishell", (str + 2));
		else
			string = ft_strdup("./minishell");
	}
	else if ((str[1] >= '1' && str[1] <= '9') && str[2] != '\0')
		string = ft_strdup(str + 2);
	else
		string = ft_strdup("");
	if (!string)
		return (NULL);
	return (string);
}

char	*fill_dollar_sign2(char **split_pos, int type, t_mini_shell *data)
{
	char	*string;
	char	*var_out;

	var_out = NULL;
	if (split_pos[0][1] != '"' && split_pos[0][1] != '\'')
	{
		var_out = ft_getenv(data, ft_strrchr(split_pos[0], '$') + 1);
		if (var_out == NULL)
			var_out = ft_strdup("");
		else if (var_out != NULL && type == 1)
		{
			string = ft_strdup(var_out);
			var_out = dollar_sgin_variable_check(string);
			free(string);
		}
		else if (var_out != NULL && type == 0)
			var_out = ft_strdup(var_out);
	}
	else if (split_pos[0][1] == '"')
		var_out = ft_strdup(ft_strchr(split_pos[0], '$') + 1);
	return (var_out);
}

int	fill_dollar_sign(char **split_pos, int type, t_mini_shell *data)
{
	char	*var_out;

	var_out = NULL;
	if (split_pos[0][0] == '$' && split_pos[0][1] == '\0')
		var_out = ft_strdup("$");
	else if (split_pos[0][0] == '$' && split_pos[0][1] == '?')
		var_out = ft_itoa(data->save_exit_status);
	else if (split_pos[0][1] >= '0' && split_pos[0][1] <= '9')
		var_out = num_after_dollar_sign(split_pos[0]);
	else
		var_out = fill_dollar_sign2(split_pos, type, data);
	if (!var_out)
		return (FAILURE);
	free(split_pos[0]);
	split_pos[0] = var_out;
	return (SUCCESS);
}

char	*ft_pre_string(char *split_cmd, char *pos)
{
	int		offset;
	char	*pre_string;

	offset = pos - split_cmd;
	pre_string = malloc(offset + 1);
	if (!pre_string)
		return (NULL);
	pre_string = ft_strncpy(pre_string, split_cmd, offset);
	pre_string[offset] = '\0';
	return (pre_string);
}

char	*collect_string(t_expander *expander)
{
	char	*last_string;
	char	*temp;
	int		i;

	i = 1;
	last_string = ft_strjoin(expander->pre_string, expander->split_pos[0]);
	if (!last_string)
		return (NULL);
	while (expander->split_pos[i])
	{
		temp = ft_strjoin(" ", expander->split_pos[i]);
		expander->temp = ft_strjoin(last_string, temp);
		free(temp);
		free(last_string);
		if (!expander->temp)
			return (NULL);
		last_string = expander->temp;
		i++;
	}
	free(expander->pre_string);
	ft_free_tow_d_array(expander->split_pos);
	expander->pre_string = NULL;
	expander->split_pos = NULL;
	return (last_string);
}
