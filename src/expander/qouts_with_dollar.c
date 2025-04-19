/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qouts_with_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:11:20 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:35:44 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*dollar_with_single3(char **array, int n, int flag, t_mini_shell *data)
{
	char	**cmd;
	char	*str;
	char	*string;

	if ((array[n][0] == '$' && array[n][1] == '\''
			&& array[n][ft_strlen(array[n]) - 1] != '\''))
		flag = 1;
	string = ft_strdup(array[n]);
	if (!string)
		return (NULL);
	if (flag == 0)
		string[ft_strlen(string) - 1] = '\0';
	cmd = dollar_inside_single2(string, 2, data);
	if (!cmd)
	{
		free(string);
		return (NULL);
	}
	str = toknes_join(cmd);
	ft_free_tow_d_array(cmd);
	free(string);
	if (!str)
		return (NULL);
	str = add_single_with_dollar(str, flag);
	return (str);
}

int	dollar_with_single(char **array, int n, t_mini_shell *data)
{
	char	*str;
	int		flag;

	flag = 0;
	if ((array[n][0] == '$' && array[n][1] == '\'' && array[n][2] == '\''
			&& array[n][3] == '\0'))
	{
		free(array[n]);
		array[n] = ft_strdup("$''");
		return (SUCCESS);
	}
	str = dollar_with_single3(array, n, flag, data);
	if (!str)
		return (FAILURE);
	free(array[n]);
	array[n] = str;
	return (SUCCESS);
}

char	**dollar_inside_single2(char *string, int type, t_mini_shell *data)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = tokens(string + type);
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			if (!dollar_sign(cmd, i, 0, data))
			{
				ft_free_tow_d_array(cmd);
				return (NULL);
			}
		}
		i++;
	}
	return (cmd);
}

char	*dollar_inside_single3(char **array, int n, int flag,
		t_mini_shell *data)
{
	char	**cmd;
	char	*str;
	char	*string;

	if ((array[n][0] == '\'' && array[n][ft_strlen(array[n]) - 1] != '\''))
		flag = 1;
	string = ft_strdup(array[n]);
	if (!string)
		return (NULL);
	if (flag == 0)
		string[ft_strlen(string) - 1] = '\0';
	cmd = dollar_inside_single2(string, 1, data);
	if (!cmd)
	{
		free(string);
		return (NULL);
	}
	str = toknes_join(cmd);
	ft_free_tow_d_array(cmd);
	free(string);
	if (!str)
		return (NULL);
	str = add_single(str, flag);
	return (str);
}

int	dollar_inside_single(char **array, int n, t_mini_shell *data)
{
	int		flag;
	char	*str;

	flag = 0;
	if ((array[n][0] == '\'' && array[n][1] == '\'' && array[n][2] == '\0'))
	{
		free(array[n]);
		array[n] = ft_strdup("''");
		if (!array[n])
			return (FAILURE);
		return (SUCCESS);
	}
	str = dollar_inside_single3(array, n, flag, data);
	if (!str)
		return (FAILURE);
	free(array[n]);
	array[n] = str;
	return (SUCCESS);
}
