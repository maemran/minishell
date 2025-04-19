/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:02:59 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:13 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_initialize_expander(t_expander *expander)
{
	expander->pre_string = NULL;
	expander->split_pos = NULL;
	expander->temp = NULL;
	expander->last_string = NULL;
	expander->pos = NULL;
	expander->tokens = NULL;
}

int	ft_exit_expander(t_expander *expander, char *str)
{
	if (str)
		free(str);
	if (!expander)
		return (FAILURE);
	if (expander->pre_string)
	{
		free(expander->pre_string);
		expander->pre_string = NULL;
	}
	if (expander->split_pos)
	{
		ft_free_tow_d_array(expander->split_pos);
		expander->split_pos = NULL;
	}
	if (expander->last_string)
	{
		free(expander->last_string);
		expander->last_string = NULL;
	}
	if (expander->temp)
		free(expander->temp);
	free(expander);
	expander = NULL;
	return (FAILURE);
}

int	is_only_one_space(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i])
	{
		if ((str[i] == ' ' && str[i + 1] == ' ') || (str[i] == ' ' && str[i
					+ 1] == '\0'))
			flag = 0;
		i++;
	}
	return (flag);
}

char	*dollar_sgin_variable_check(char *var_out)
{
	char	**split_var_out;
	char	*string;

	string = NULL;
	if (!var_out)
		return (NULL);
	if (is_only_one_space(var_out))
		string = ft_strdup(var_out);
	else
	{
		split_var_out = ft_split(var_out, ' ');
		if (split_var_out[0])
			string = join_two_d_to_string(split_var_out, " ");
		else if (!split_var_out[0])
			string = ft_strdup("");
		ft_free_tow_d_array(split_var_out);
	}
	if (!string)
		return (NULL);
	return (string);
}

t_expander	*free_struct(t_expander *expander)
{
	if (!expander)
		return (NULL);
	if (expander->pre_string)
	{
		free(expander->pre_string);
		expander->pre_string = NULL;
	}
	if (expander->split_pos)
	{
		ft_free_tow_d_array(expander->split_pos);
		expander->split_pos = NULL;
	}
	if (expander->last_string)
	{
		free(expander->last_string);
		expander->last_string = NULL;
	}
	if (expander->temp)
	{
		free(expander->temp);
		expander->temp = NULL;
	}
	free(expander);
	expander = NULL;
	return (NULL);
}
