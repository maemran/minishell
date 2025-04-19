/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:43:22 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:32:59 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	new_env(char *str, char *temp, t_mini_shell *data)
{
	char	**new_env;
	int		i;

	i = ft_two_d_len(data->env);
	if (!unset(str, data))
		return (FAILURE);
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (new_env == NULL)
		return (FAILURE);
	i = 0;
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		if (new_env[i] == NULL)
			return (ft_free_all(NULL, NULL, new_env, NULL));
		i++;
	}
	(void)temp;
	new_env[i] = ft_strdup(temp);
	if (new_env[i] == NULL)
		return (ft_free_all(NULL, NULL, new_env, NULL));
	new_env[i + 1] = NULL;
	ft_free_tow_d_array(data->env);
	data->env = new_env;
	return (SUCCESS);
}

char	*export_string_check(char *string, t_mini_shell *data)
{
	char	**split;
	char	*temp;

	split = ft_split_cmd(string, ' ');
	if (!split)
		return (NULL);
	if (ft_isalpha(split[0][0]) == 0 && split[0][0] != '_')
	{
		ft_free_tow_d_array(split);
		error_msg("not a valid identifier\n", NULL);
		data->exit_status = 1;
		return ("2");
	}
	if (!expander(split, data))
		return (free_all(NULL, NULL, split, NULL));
	temp = join_two_d_to_string(split, " ");
	ft_free_tow_d_array(split);
	if (!temp)
		return (NULL);
	return (temp);
}

int	terminate_export(char *temp)
{
	free(temp);
	return (SUCCESS);
}

int	export_string(char *string, t_mini_shell *data)
{
	char	*temp;
	char	*str;

	temp = export_string_check(string, data);
	if (!temp)
		return (FAILURE);
	if (temp[0] == '2')
		return (SUCCESS);
	if (find_env_var(temp, data, 1) == SUCCESS)
		return (terminate_export(temp));
	str = var_before_equal(temp);
	if (str == NULL)
		return (ft_free_all(temp, NULL, NULL, NULL));
	if (str[0] == '\0')
		return (terminate_export(temp));
	if (!new_env(str, temp, data))
		return (ft_free_all(str, temp, NULL, NULL));
	free(str);
	free(temp);
	return (SUCCESS);
}

int	export(char *string, t_mini_shell *data)
{
	int		i;
	char	**array;

	i = 1;
	array = ft_split_cmd(string, ' ');
	if (!array)
		return (FAILURE);
	while (array[i])
	{
		if (export_string(array[i], data) == FAILURE)
			return (ft_free_all(NULL, NULL, array, NULL));
		i++;
	}
	ft_free_tow_d_array(array);
	return (SUCCESS);
}
