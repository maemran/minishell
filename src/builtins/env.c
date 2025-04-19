/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:41:18 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:32:48 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_env_var(char *string, t_mini_shell *data, int flag)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(string);
	while (data->env[i] && flag == 0)
	{
		if (ft_strncmp(data->env[i], string, n) == 0 && data->env[i][n] == '=')
			return (SUCCESS);
		i++;
	}
	i = 0;
	while (data->env[i] && flag == 1)
	{
		if (str_comp(data->env[i], string))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	env_copy(char **env, t_mini_shell *data)
{
	int	i;

	data->env = malloc(sizeof(char *) * (ft_two_d_len(env) + 1));
	if (data->env == NULL)
		return (FAILURE);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (data->env[i] == NULL)
		{
			ft_free_tow_d_array(data->env);
			return (FAILURE);
		}
		i++;
	}
	data->env[i] = NULL;
	if (!unset("_", data))
		return (FAILURE);
	if (!modify_shell(data))
		return (FAILURE);
	if (!modify_path(data))
		return (FAILURE);
	return (SUCCESS);
}

void	env(t_mini_shell *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		ft_putstr_fd(data->env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

char	*ft_getenv(t_mini_shell *data, char *var)
{
	int	n;
	int	i;
	int	flag;

	i = 0;
	n = ft_strlen(var);
	flag = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, n) == 0 && data->env[i][n] == '=')
		{
			n++;
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		return (NULL);
	return (data->env[i] + n);
}
