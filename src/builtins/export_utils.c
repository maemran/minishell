/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:06:09 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:32:53 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**join_export(char **sorted_env)
{
	char	**env_with_export;
	int		i;

	i = 0;
	env_with_export = malloc(sizeof(char *) * (ft_two_d_len(sorted_env) + 1));
	if (env_with_export == NULL)
		return (NULL);
	while (sorted_env[i])
	{
		env_with_export[i] = ft_strjoin("declare -x ", sorted_env[i]);
		if (env_with_export[i] == NULL)
		{
			ft_free_tow_d_array(env_with_export);
			return (NULL);
		}
		i++;
	}
	env_with_export[i] = NULL;
	return (env_with_export);
}

void	pubble_sort(t_mini_shell *data)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (data->sorted_env[i])
	{
		j = 0;
		while (data->sorted_env[j])
		{
			if (data->sorted_env[j + 1] && (ft_strncmp(data->sorted_env[j],
						data->sorted_env[j + 1],
						ft_strlen(data->sorted_env[j])) > 0))
			{
				temp = data->sorted_env[j];
				data->sorted_env[j] = data->sorted_env[j + 1];
				data->sorted_env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	sort_export(t_mini_shell *data)
{
	char	**join_sorted;

	data->sorted_env = ft_strdup_two_d(data->env);
	if (!data->sorted_env)
		return (FAILURE);
	pubble_sort(data);
	join_sorted = join_export(data->sorted_env);
	ft_free_tow_d_array(data->sorted_env);
	if (join_sorted == NULL)
		return (FAILURE);
	data->sorted_env = join_sorted;
	ft_two_d_print(data->sorted_env);
	ft_free_tow_d_array(data->sorted_env);
	data->sorted_env = NULL;
	return (SUCCESS);
}

void	error_msg(char *str1, char *str2)
{
	write(2, ERORR_MSG, ft_strlen(ERORR_MSG));
	write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, str2, ft_strlen(str2));
}

char	*free_all(char *str1, char *str2, char **str3, char **str4)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		ft_free_tow_d_array(str3);
	if (str4)
		ft_free_tow_d_array(str4);
	return (NULL);
}
