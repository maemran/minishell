/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:25:22 by salshaha          #+#    #+#             */
/*   Updated: 2025/04/19 03:36:53 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*tokens_qouts(char *str, t_expander *tokens, char **result)
{
	char	quote;
	int		start;

	quote = str[tokens->i];
	start = tokens->i++;
	while (str[tokens->i] && str[tokens->i] != quote)
		tokens->i++;
	if (str[tokens->i])
		tokens->i++;
	result[tokens->count] = malloc(tokens->i - start + 1);
	if (!result[tokens->count])
		return (NULL);
	ft_strncpy(result[tokens->count], &str[start], tokens->i - start);
	result[tokens->count][tokens->i - start] = '\0';
	tokens->count++;
	return ("");
}

char	*tokens_dollar(char *str, t_expander *tokens, char **result)
{
	char	quote;
	int		start;

	start = tokens->i++;
	if (str[tokens->i] == '"' || str[tokens->i] == '\'')
	{
		quote = str[tokens->i++];
		while (str[tokens->i] && str[tokens->i] != quote)
			tokens->i++;
		if (str[tokens->i])
			tokens->i++;
	}
	else
	{
		while (str[tokens->i] && !is_delimiter(str[tokens->i])
			&& str[tokens->i] != ' ')
			tokens->i++;
	}
	result[tokens->count] = malloc(tokens->i - start + 1);
	if (!result[tokens->count])
		return (NULL);
	ft_strncpy(result[tokens->count], &str[start], tokens->i - start);
	result[tokens->count][tokens->i - start] = '\0';
	tokens->count++;
	return ("");
}

char	*tokens_others(char *str, t_expander *tokens, char **result)
{
	while (str[tokens->i] == ' ')
		tokens->i++;
	if (str[tokens->i] == '~' || str[tokens->i] == '+' || str[tokens->i] == '-'
		|| str[tokens->i] == '=' || str[tokens->i] == '#'
		|| str[tokens->i] == '%' || str[tokens->i] == '@'
		|| str[tokens->i] == '^')
	{
		result[tokens->count] = string_type(tokens, str);
		if (!result[tokens->count])
			return (NULL);
		tokens->count++;
		tokens->i++;
	}
	else
	{
		if (!tokens_others2(str, tokens, result))
			return (NULL);
	}
	return ("");
}

char	*tokens_others2(char *str, t_expander *tokens, char **result)
{
	int	start;

	start = tokens->i;
	while (str[tokens->i] && !is_delimiter(str[tokens->i])
		&& str[tokens->i] != ' ')
		tokens->i++;
	result[tokens->count] = malloc(tokens->i - start + 1);
	if (!result[tokens->count])
		return (NULL);
	ft_strncpy(result[tokens->count], &str[start], (tokens->i) - start);
	result[tokens->count][tokens->i - start] = '\0';
	tokens->count++;
	return ("");
}

char	**ft_exit_tokens(t_expander *tokens, char **result)
{
	if (result)
		ft_free_tow_d_array(result);
	if (!tokens)
		return (NULL);
	if (tokens->tokens)
		ft_free_tow_d_array(tokens->tokens);
	if (tokens)
		free(tokens);
	return (NULL);
}
