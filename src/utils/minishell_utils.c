/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:39:57 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:37:40 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_free_all(char *str1, char *str2, char **str3, char **str4)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		ft_free_tow_d_array(str3);
	if (str4)
		ft_free_tow_d_array(str4);
	return (FAILURE);
}

void	ft_initialize_minishell(t_mini_shell *data)
{
	data->saved_exit = 0;
	data->delimiter_num = -1;
	data->here_doc_num = 0;
	data->syntax_error = 0;
	data->pipe = 0;
	data->before = 0;
	data->here_with_error = 0;
	data->terminate_process = 0;
	data->exit_status = 0;
	data->save_exit_status = 0;
	data->oldpwd = NULL;
	data->underscore = NULL;
	data->sorted_env = NULL;
	data->shlvl = NULL;
	data->env = NULL;
}

void	free_minishell_struct(t_mini_shell *data)
{
	if (data->shlvl)
	{
		free(data->shlvl);
		data->shlvl = NULL;
	}
	if (data->underscore)
	{
		free(data->underscore);
		data->underscore = NULL;
	}
	if (data->oldpwd)
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
	if (data->env)
		ft_free_tow_d_array(data->env);
	if (data->sorted_env)
		ft_free_tow_d_array(data->sorted_env);
	if (data)
		free(data);
}

void	main_exit(t_mini_shell *data)
{
	error_msg("Out of memory\n", NULL);
	free_minishell_struct(data);
	exit(1);
}

int	is_only_spaces(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			count++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}
