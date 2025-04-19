/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:35:07 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:32:10 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**unset2(char *string, char **new_env, t_mini_shell *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (!(ft_strncmp(data->env[i], string, ft_strlen(string)) == 0
				&& data->env[i][ft_strlen(string)] == '='))
		{
			new_env[j] = ft_strdup(data->env[i]);
			if (new_env[j] == NULL)
			{
				ft_free_tow_d_array(new_env);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	unset(char *string, t_mini_shell *data)
{
	char	**new_env;

	if (find_env_var(string, data, 0) == FAILURE)
		return (SUCCESS);
	new_env = (char **)malloc(sizeof(char *) * ft_two_d_len(data->env));
	if (new_env == NULL)
		return (FAILURE);
	if (!unset2(string, new_env, data))
		return (ft_free_all(NULL, NULL, new_env, NULL));
	ft_free_tow_d_array(data->env);
	data->env = new_env;
	return (SUCCESS);
}

int	unset_string(char *string, t_mini_shell *data)
{
	int		i;
	char	**array;

	i = 1;
	array = ft_split_cmd(string, ' ');
	if (!array)
		return (FAILURE);
	while (array[i])
	{
		if (unset(array[i], data) == FAILURE)
			return (ft_free_all(NULL, NULL, array, NULL));
		i++;
	}
	ft_free_tow_d_array(array);
	return (SUCCESS);
}

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
		free(cwd);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}
