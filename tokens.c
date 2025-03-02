/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:30:00 by maemran           #+#    #+#             */
/*   Updated: 2025/02/28 01:49:27 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **ft_exit_tokens(t_expander *tokens, char **result)
{
    if (tokens)
        free(tokens);
    if (result)
        ft_free_tow_d_array(result);
    //ft_putstr_fd("\033[1;31mminishell:\033[0m Out of memory\n", 2);///i t should be put in main
    return (NULL);
}

int is_delimiter(char c) 
{
    if (c == '"' || c == '\'' || c == '$' || c == '~')
        return (1);
    return (0);
}

char    *tokens_qouts(char *str, t_expander *tokens, char **result)
{
    char    quote;
    int start;
    
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
    return("");
}

char    *tokens_dollar(char *str ,t_expander *tokens, char **result)
{
    char    quote;
    int start;
    
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
        while (str[tokens->i] && !is_delimiter(str[tokens->i]) && str[tokens->i] != ' ')
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

char    *tokens_others(char *str ,t_expander *tokens, char **result)
{
    int start;
    
    if (str[tokens->i] == '~')
    {
        result[tokens->count] = ft_strdup("~");
        if (!result[tokens->count])
            return (NULL);
        tokens->count++;
        tokens->i++;
    }
    else 
    {
        start = tokens->i;
        while (str[tokens->i] && !is_delimiter(str[tokens->i]) && str[tokens->i] != ' ')
            tokens->i++;
        result[tokens->count] = malloc(tokens->i - start + 1);
        if (!result[tokens->count])
            return (NULL);
        ft_strncpy(result[tokens->count], &str[start], (tokens->i) - start);
        result[tokens->count][tokens->i - start] = '\0';
        tokens->count++;
    }
    return ("");
}

char    *tokens2(t_expander *tokens, char *str, char **result)
{
    char    *null_check;

    null_check = "";
    while (str[tokens->i] && null_check)
    {
        if (str[tokens->i] == '"' || str[tokens->i] == '\'')
            null_check = tokens_qouts(str, tokens, result);
        else if (str[tokens->i] == '$')
            null_check = tokens_dollar(str ,tokens, result);
        else
            null_check = tokens_others(str ,tokens, result);
    }
    return (null_check);
}

char    **tokens(char *str)
{
    int token_count;
    char **result;
    char    *null_check;
    t_expander  *tokens;

    tokens = malloc(sizeof(t_expander));
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
        return(ft_exit_tokens(tokens, result));
    result[tokens->count] = NULL;
    free(tokens);
    return (result);
}

