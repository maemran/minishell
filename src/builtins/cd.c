/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 02:12:39 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:32:29 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*cd1(t_mini_shell *data, char *full_cmd, char *path)
{
	char	**array;

	array = ft_split_cmd(full_cmd, ' ');
	if (!array)
		return (NULL);
	if (ft_two_d_len(array) == 1)
	{
		path = ft_getenv(data, "HOME");
		if (!path)
		{
			ft_free_tow_d_array(array);
			return ("");
		}
	}
	else if (ft_two_d_len(array) > 2)
	{
		error_msg("too many arguments\n", NULL);
		data->exit_status = 1;
		ft_free_tow_d_array(array);
		return ("2");
	}
	ft_free_tow_d_array(array);
	return (path);
}

char	*cd2(t_mini_shell *data, char *str1)
{
	char	*str2;
	char	*var;

	data->oldpwd = ft_strdup(str1);
	if (!data->oldpwd)
		return (NULL);
	str2 = getcwd(NULL, 0);
	if (!str2)
		return (NULL);
	var = ft_strjoin("PWD=", str2);
	free(str2);
	if (!var)
		return (NULL);
	if (!export_string(var, data))
		return (free_all(NULL, var, NULL, NULL));
	free(var);
	if (!unset("OLDPWD", data))
		return (NULL);
	var = ft_strjoin("OLDPWD=", data->oldpwd);
	if (!var)
		return (NULL);
	free(data->oldpwd);
	data->oldpwd = NULL;
	return (var);
}

int	cd3(char *path, t_mini_shell *data)
{
	if (chdir(path) != 0)
	{
		error_msg("No such file or directory\n", NULL);
		data->exit_status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	cd(char *path, t_mini_shell *data, char *full_cmd)
{
	char	*str1;
	char	*var;

	path = cd1(data, full_cmd, path);
	if (!path)
		return (FAILURE);
	if (path[0] == '2')
		return (SUCCESS);
	str1 = getcwd(NULL, 0);
	if (!str1)
		return (FAILURE);
	if (!cd3(path, data))
		return (ft_free_all(str1, NULL, NULL, NULL));
	if (!unset("PWD", data))
		return (FAILURE);
	var = cd2(data, str1);
	if (!var)
		return (ft_free_all(str1, NULL, NULL, NULL));
	if (export_string(var, data) == 0)
		return (ft_free_all(str1, var, NULL, NULL));
	free(var);
	free(str1);
	return (SUCCESS);
}
