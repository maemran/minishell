/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:59:59 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 08:43:23 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (FAILURE);
	while (str[i])
	{
		if (str[i] == ' ')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	num_of_spaces(char *str, t_mini_shell *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[1] == ' ' && str[0] == '"')
	{
		count = 1;
		while (str[i] == ' ')
			i++;
		data->before = 1;
	}
	while (str[i])
	{
		if (((str[i] >= 1 && str[i] <= 126) && str[i + 1] == ' ')
			&& !(str[i] == ' ' && str[i + 1] == ' '))
			count++;
		i++;
	}
	return (count);
}

int	*fill_spaces(int *spaces, char *str, int *i, int *j)
{
	int	count;

	count = 0;
	while (str[*i])
	{
		if (str[*i] == ' ')
		{
			while (str[*i] == ' ')
			{
				(*i)++;
				count++;
			}
			spaces[*j] = count;
			(*j)++;
		}
		count = 0;
		(*i)++;
	}
	spaces[*j] = -1;
	return (spaces);
}

int	*spaces(char *str, t_mini_shell *data)
{
	int	i;
	int	j;
	int	*spaces;

	i = 0;
	j = 0;
	spaces = malloc(sizeof(int) * (num_of_spaces(str, data) + 1));
	if (!spaces)
		return (NULL);
	if (str[0] == ' ')
	{
		while (str[i] == ' ')
			i++;
		j = 1;
		spaces[0] = i;
	}
	spaces = fill_spaces(spaces, str, &i, &j);
	return (spaces);
}
