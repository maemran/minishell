/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_for_tokenizer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:46:18 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 08:13:26 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	delimiter(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ')
		return (SUCCESS);
	return (FAILURE);
}

void	delimiters_type(char *str, int *i)
{
	if (delimiter(str[*i]))
	{
		if ((str[*i] == '<' && str[(*i) + 1] == '<') || (str[*i] == '>'
				&& str[(*i) + 1] == '>'))
			(*i) += 2;
		else
			(*i)++;
	}
	else
	{
		while (str[*i] && !delimiter(str[*i]))
		{
			if (str[*i] == '"' || str[*i] == '\'')
				*i = find_qouts(str, (*i) - 1, *i);
			(*i)++;
		}
	}
}

int	count_token(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		delimiters_type(str, &i);
		count++;
	}
	return (count);
}

char	**fill_tokens(t_expander *expander, char *str)
{
	int	start;

	start = 0;
	while (str[expander->i] && expander->count < count_token(str))
	{
		while (str[expander->i] == ' ')
			expander->i++;
		if (!str[expander->i])
			break ;
		start = expander->i;
		delimiters_type(str, &(expander->i));
		expander->tokens[expander->count] = malloc((expander->i) - start + 1);
		if (!expander->tokens[expander->count])
			return (ft_exit_tokens(expander, NULL));
		ft_strncpy(expander->tokens[expander->count], str + start, (expander->i)
			- start);
		expander->tokens[expander->count][(expander->i) - start] = '\0';
		expander->count++;
	}
	expander->tokens[expander->count] = NULL;
	return (expander->tokens);
}

char	**tokens_for_tokenizer(char *str)
{
	t_expander	*expander;
	char		**array;

	expander = malloc(sizeof(t_expander));
	ft_initialize_expander(expander);
	if (!expander)
		return (NULL);
	expander->i = 0;
	expander->count = 0;
	expander->tokens = malloc((count_token(str) + 1) * sizeof(char *));
	if (!expander->tokens)
		return (ft_exit_tokens(expander, NULL));
	if (!fill_tokens(expander, str))
		return (NULL);
	array = ft_strdup_two_d(expander->tokens);
	if (!array)
		return (ft_exit_tokens(expander, NULL));
	ft_free_tow_d_array(expander->tokens);
	free(expander);
	return (array);
}
