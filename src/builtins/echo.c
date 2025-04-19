/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:39:40 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:32:35 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_echo_args(char **str, int i)
{
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	dash_n_check(char **str, int i)
{
	int	j;

	j = 1;
	while (str[i][j])
	{
		if (str[i][j] != 'n' && str[i][j] != 'e' && str[i][j] != 'E')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	echo_with_n(char **str)
{
	int	i;

	i = 1;
	if (i == 1 && dash_n_check(str, i) == 0)
		return (FAILURE);
	while (str[i] != NULL && (ft_strncmp(str[i], "-n", 2) == 0)
		&& dash_n_check(str, i))
		i++;
	if (str[i] == NULL)
	{
		ft_putstr_fd("", 1);
		return (2);
	}
	print_echo_args(str, i);
	return (SUCCESS);
}

char	**echo1(char *string, t_mini_shell *data)
{
	char	**array;
	char	**str;

	str = ft_split_cmd(string, ' ');
	if (!str)
		return (NULL);
	array = ft_strdup_two_d(str);
	ft_free_tow_d_array(str);
	if (!array)
		return (NULL);
	if (!expander(array, data))
	{
		ft_free_tow_d_array(array);
		return (NULL);
	}
	return (array);
}

int	echo(char *string, t_mini_shell *data)
{
	char	**str;

	str = echo1(string, data);
	if (!str)
		return (FAILURE);
	if (str[1] == NULL)
	{
		ft_free_tow_d_array(str);
		ft_putchar_fd('\n', 1);
		return (SUCCESS);
	}
	if (!ft_strncmp(str[0], "echo", 4) && !ft_strncmp(str[1], "-n", 2))
	{
		if (echo_with_n(str) == 0)
		{
			print_echo_args(str, 1);
			ft_putchar_fd('\n', 1);
		}
		ft_free_tow_d_array(str);
		return (SUCCESS);
	}
	print_echo_args(str, 1);
	ft_putchar_fd('\n', 1);
	ft_free_tow_d_array(str);
	return (SUCCESS);
}
