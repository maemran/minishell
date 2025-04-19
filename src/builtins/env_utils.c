/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:37:17 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:32:41 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	modify_shell(t_mini_shell *data)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup(getenv("PWD"));
	if (temp1 == NULL)
		return (SUCCESS);
	temp2 = ft_strjoin(temp1, "/minishell");
	free(temp1);
	if (temp2 == NULL)
		return (FAILURE);
	temp1 = ft_strjoin("SHELL=", temp2);
	free(temp2);
	if (temp1 == NULL)
		return (FAILURE);
	if (!unset("SHELL", data))
		return (ft_free_all(temp1, NULL, NULL, NULL));
	if (!export_string(temp1, data))
		return (ft_free_all(temp1, NULL, NULL, NULL));
	free(temp1);
	return (SUCCESS);
}

char	*modify_path2(t_mini_shell *data)
{
	char	*temp1;
	char	*temp2;
	char	*path;

	temp1 = getcwd(NULL, 0);
	if (temp1 == NULL)
		return (NULL);
	temp2 = ft_strjoin(getenv("PATH"), ":");
	if (temp2 == NULL)
	{
		free(temp1);
		data->exit_status = 1;
		return ("2");
	}
	path = ft_strjoin(temp2, temp1);
	free(temp2);
	free(temp1);
	if (path == NULL)
		return (NULL);
	return (path);
}

int	modify_path(t_mini_shell *data)
{
	char	*temp1;
	char	*path;

	if (!getenv("PATH"))
		return (SUCCESS);
	path = modify_path2(data);
	if (!path)
		return (FAILURE);
	if (path[0] == '2')
		return (SUCCESS);
	temp1 = ft_strjoin("PATH=", path);
	free(path);
	if (temp1 == NULL)
		return (FAILURE);
	if (!unset("PATH", data))
		return (ft_free_all(temp1, NULL, NULL, NULL));
	if (!export_string(temp1, data))
		return (ft_free_all(temp1, NULL, NULL, NULL));
	free(temp1);
	return (SUCCESS);
}

char	*var_before_equal(char *string)
{
	char	*pos;
	char	*str;

	pos = ft_strchr(string, '=');
	if (pos == NULL)
		return ("");
	str = ft_pre_string(string, pos);
	if (str == NULL)
		return (NULL);
	return (str);
}
