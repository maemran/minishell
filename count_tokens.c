/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:45:06 by maemran           #+#    #+#             */
/*   Updated: 2025/02/28 18:19:58 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    count_tokens_qouts(t_expander *tokens, char *str)
{
    char    quote;

    quote = str[tokens->i++];
    tokens->count++;
    while (str[tokens->i] && str[tokens->i] != quote) 
        tokens->i++;
    if (str[tokens->i]) 
        tokens->i++;
}

void    count_tokens_dollar(t_expander *tokens, char *str)
{
    char    quote;

    tokens->count++;
    tokens->i++;
    if (str[tokens->i] == '$' || str[tokens->i] == '\'') 
    {
        quote = str[tokens->i++];
        while (str[tokens->i] && str[tokens->i] != quote)
            tokens->i++;
        if (str[tokens->i])
            tokens->i++;
    }
    else
    {
        while (str[tokens->i] && !is_delimiter(str[tokens->i]) && str[tokens->i] != ' ')
            tokens->i++;
    }

}

void    count_tokens_others(t_expander *tokens, char *str)
{
    if (str[tokens->i] == '~') 
    {
        tokens->count++;
        tokens->i++;
    } 
    else 
    {
        tokens->count++;
        while (str[tokens->i] && !is_delimiter(str[tokens->i]) && str[tokens->i] != ' ')
            tokens->i++;
    }
}

int count_tokens(char *str, t_expander *tokens)
{
    tokens->i = 0;
    tokens->count = 0;
    while (str[tokens->i]) 
    {
        if (str[tokens->i] == '"' || str[tokens->i] == '\'') 
            count_tokens_qouts(tokens, str);
        else if (str[tokens->i] == '$')
            count_tokens_dollar(tokens, str);
        else 
            count_tokens_others(tokens, str);
    }
    return tokens->count;
}

char    *toknes_join(char **cmds)
{
    int i;
    char *string;
    char *temp;

    i = 1;
    if (!cmds)
        return (NULL);
    string = ft_strdup(cmds[0]);
    if (!string)
        return (NULL);
    while(cmds[i])
    {
        temp = ft_strjoin(string, cmds[i]);
		if (!temp)
		{
			free(string);
			return (NULL);
		}
        free(string);
        string = temp;
        i++;
    }
    return(string);
}
