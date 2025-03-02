/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_qouts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:11:54 by maemran           #+#    #+#             */
/*   Updated: 2025/02/28 01:24:51 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*OK*/
int ft_exit_double_qouts(char **array)
{
    ft_free_tow_d_array(array);
    return (FAILURE);
}

/*OK*/
char    *join_two_d_to_string(char **cmds, char *c)
{
    int i;
    char *string;
    char *temp1;
    char    *temp2;

    i = 1;
    string = ft_strdup(cmds[0]);
    if (!string)
        return (NULL);
    while(cmds[i])
    {
        temp2 = ft_strjoin(c, cmds[i]);
        temp1 = ft_strjoin(string, temp2);
        free(temp2);
        free(string);
        if (!temp1)
            return (NULL);
        string = temp1;
        i++;
    }
    return(string);
}
/*OK*/
char    *double_qouts_expand(char *split_cmd)
{
    char    **cmds;
    char    *string;
    int i;
    
    i = 0;
    cmds = tokens(split_cmd);
    if (!cmds)
        return (NULL);
    while (cmds[i])
    {
        if (cmds[i][0] == '$' && cmds[i][1] == '\'')
            break ;
        if (cmds[i][0] == '$')
        {
            if (!(dollar_sign(cmds[i], cmds, i, 0)))
            {
                ft_free_tow_d_array(cmds);
                return(NULL);
            }
        }
        i++;
    }
    string = toknes_join(cmds);
    ft_free_tow_d_array(cmds);
    return (string);
}
/*OK*/
int    double_qouts(char *split_cmd, char **string_cmd, int n)
{
    char    **split_input;
    char    *last_string;
    char    *string;
    int i;

    i = 0;
    if ((split_cmd[0] == '"' && split_cmd[1] == '\0') 
        || (split_cmd[0] == '"' && split_cmd[ft_strlen(split_cmd) - 1] != '"'))
    {
        string_cmd[n] = ft_strdup("");
        if (!string_cmd[n])
            return (FAILURE);
        return (SUCCESS);
    }
    split_input = ft_split_cmd(split_cmd + 1, ' ');
    if (!split_input)
        return (FAILURE);
    while(split_input[i])
    {
        string = double_qouts_expand(split_input[i]);
        if (!string)
            return (ft_exit_double_qouts(split_input));
        free(split_input[i]);
        split_input[i] = string;
        i++;
    }
    string = join_two_d_to_string(split_input, " ");
    ft_free_tow_d_array(split_input);
    if (!string)
        return (FAILURE);
    if (string[ft_strlen(string) - 1] == '"')
        string[ft_strlen(string) - 1] = '\0';
    last_string = pipe_check(string);
    free(string);
    if (!last_string)
        return (FAILURE);
    free(string_cmd[n]);
    string_cmd[n] = last_string;
    printf("double_qouts = %s\n",  string_cmd[n]);
    return (SUCCESS);
}
