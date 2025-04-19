/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:30:00 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 04:39:16 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_delimiter(char c)
{
	if (c == '"' || c == '\'' || c == '$' || c == '~' || c == '+' || c == '-'
		|| c == '=' || c == '#' || c == '%' || c == '@' || c == '^')
		return (1);
	return (0);
}

char	*string_type(t_expander *tokens, char *str)
{
	if (str[tokens->i] == '~')
		return (ft_strdup("~"));
	else if (str[tokens->i] == '+')
		return (ft_strdup("+"));
	else if (str[tokens->i] == '-')
		return (ft_strdup("-"));
	else if (str[tokens->i] == '=')
		return (ft_strdup("="));
	else if (str[tokens->i] == '#')
		return (ft_strdup("#"));
	else if (str[tokens->i] == '%')
		return (ft_strdup("%"));
	else if (str[tokens->i] == '@')
		return (ft_strdup("@"));
	else if (str[tokens->i] == '^')
		return (ft_strdup("^"));
	return ("");
}

char	*tokens2(t_expander *tokens, char *str, char **result)
{
	char	*null_check;

	null_check = "";
	while (str[tokens->i] && null_check)
	{
		if (str[tokens->i] == '"' || str[tokens->i] == '\'')
			null_check = tokens_qouts(str, tokens, result);
		else if (str[tokens->i] == '$')
			null_check = tokens_dollar(str, tokens, result);
		else
			null_check = tokens_others(str, tokens, result);
	}
	return (null_check);
}

char	**make_empty_string(char *string)
{
	int		count;
	char	**str;
	int		i;

	count = 0;
	i = 0;
	while (string[count] && string[count] == ' ')
		count++;
	str = malloc(sizeof(char *) * 2);
	if (!str)
		return (NULL);
	str[0] = malloc(sizeof(char) * (count + 1));
	while (string[i])
	{
		str[0][i] = string[i];
		i++;
	}
	str[0][i] = '\0';
	str[1] = NULL;
	return (str);
}

char	**tokens(char *str)
{
	int			token_count;
	char		**result;
	char		*null_check;
	t_expander	*tokens;

	if (is_only_spaces(str))
		return (make_empty_string(str));
	tokens = malloc(sizeof(t_expander));
	ft_initialize_expander(tokens);
	if (!tokens)
		ft_exit_tokens(NULL, NULL);
	token_count = count_tokens(str, tokens);
	result = malloc((token_count + 1) * sizeof(char *));
	if (!result)
		ft_exit_tokens(tokens, NULL);
	tokens->count = 0;
	tokens->i = 0;
	null_check = tokens2(tokens, str, result);
	if (!null_check)
		return (ft_exit_tokens(tokens, result));
	result[tokens->count] = NULL;
	free(tokens);
	return (result);
}
