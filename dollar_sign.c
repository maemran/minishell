/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:22:56 by maemran           #+#    #+#             */
/*   Updated: 2025/02/28 01:51:46 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*OK*/
void    ft_initialize_expander(t_expander *expander)
{
    expander->pre_string = NULL;
    expander->split_pos = NULL;
    expander->temp = NULL;
    expander->last_string = NULL;
}
/*OK*/
int    ft_exit_expander(t_expander *expander)
{
    if (expander->pre_string)
        free(expander->pre_string);
    if (expander->split_pos)
        ft_free_tow_d_array(expander->split_pos);
    if (expander->temp)
        free(expander->temp);
    if (expander->last_string)
        free(expander->last_string);
    free(expander);
    return (FAILURE);   
}

/*OK*/
int is_only_one_space(char *str)
{
    int i;
    int flag;

    i = 0;
    flag = 1;
    while (str[i])
    {
        if ((str[i] == ' ' && str[i + 1] == ' ') 
            || (str[i] == ' ' && str[i + 1] == '\0'))
            flag = 0;
        i++;
    }
    return (flag);
}
/*OK*/
char *dollar_sgin_variable_check(char *var_out)
{
    char **split_var_out;
    char *string;

    string = NULL;
    if (!var_out)
        return (NULL);
    if (is_only_one_space(var_out))
        string = ft_strdup(var_out);
    else
    {
        split_var_out = ft_split(var_out, ' ');
        if (split_var_out[0])
            string = join_two_d_to_string(split_var_out, " ");
        else if (!split_var_out[0])
            string = ft_strdup("");
        ft_free_tow_d_array(split_var_out);
    }
    if (!string)
        return (NULL);
    return (string);
}
/*OK*/
char    *num_after_dollar_sign(char *str)
{
    char    *string;
    
    if (str[1] == '0')
    {
        string = ft_strjoin("-minishell", (str + 2));
    }
    else if ((str[1] >= '1' && str[1] <= '9') && str[2] != '\0')
        string = ft_strdup(str + 2);
    else
        string = ft_strdup("");
    if (!string)
        return (NULL);
    return(string);
}
/*OK*/
int fill_dollar_sign(char **split_pos, int type)
{
    char *var_out;
    char    *string;
    
    var_out = NULL;
    if (split_pos[0][0] == '$' && split_pos[0][1] == '\0')
        var_out = ft_strdup("$");
    else if (split_pos[0][1] >= '0' && split_pos[0][1] <= '9')
        var_out = num_after_dollar_sign(split_pos[0]);
    else if (split_pos[0][1] != '"' && split_pos[0][1] != '\'')
    {
        var_out = getenv(ft_strrchr(split_pos[0], '$') + 1);
        if (var_out == NULL)
            var_out = ft_strdup("");
        else if (var_out != NULL && type == 1)
        {
            string = ft_strdup(var_out);
            var_out = dollar_sgin_variable_check(string);
            free(string);
            string = var_out;
            var_out = pipe_check(string);
            free(string);
        }
        else if (var_out != NULL && type == 0)
            var_out = ft_strdup(var_out);
    }
    else if (split_pos[0][1] == '"')
        var_out = ft_strdup(ft_strchr(split_pos[0], '$') + 1);
    if (!var_out)
        return (FAILURE);
    free(split_pos[0]);
    split_pos[0] = var_out;
    return (SUCCESS);
}
/*OK*/
char    *ft_pre_string(char *split_cmd, char *pos)
{
    int offset;
    char *pre_string;

    offset = pos - split_cmd;
    pre_string = malloc(offset + 1);
    if (!pre_string)
        return (NULL);
    pre_string = ft_strncpy(pre_string, split_cmd, offset);
    pre_string[offset] = '\0';
    return (pre_string);
}

/*OK*/
char    *collect_string(t_expander *expander)
{
    char    *last_string;
    char    *temp;
    int i;

    i = 1;
    last_string = ft_strjoin(expander->pre_string, expander->split_pos[0]);
    if (!last_string)
        return (NULL);
    while (expander->split_pos[i])
    {
        temp = ft_strjoin(" ", expander->split_pos[i]);
        expander->temp = ft_strjoin(last_string, temp);
        free (temp);
        free(last_string);
        if (!expander->temp)
            return (NULL);
        last_string = expander->temp;
        i++;
    }
    free(expander->pre_string);
    ft_free_tow_d_array(expander->split_pos);
    return (last_string);
}

int dollar_sign(char *split_cmd, char **cmds, int n, int type)
{
    int flag;
    t_expander *expander;

    flag = 0;
    if (ft_strncmp("$\"", split_cmd, 3) == 0)
    {
        free(cmds[n]);
        cmds[n] = ft_strdup("$");
        if (!cmds[n])//free(expander->split_pos)
            return (FAILURE);
        return (SUCCESS);
    }
    if (split_cmd[0] == '$' && split_cmd[1] == '\'')
    {
        single_qouts(split_cmd + 1, cmds, n);
        return (SUCCESS);
    }
    if (split_cmd[0] == '$' && split_cmd[1] == '\"')
    {
        if (!(double_qouts(split_cmd + 1, cmds, n)))
            return (FAILURE);
        return (SUCCESS);
    }
    expander = malloc(sizeof(t_expander));
    if (!expander)
        return (FAILURE);//// seq
    ft_initialize_expander(expander);
    expander->pos = ft_strchr(split_cmd, '$');
    expander->pre_string = ft_pre_string(split_cmd, expander->pos);
    if (!expander->pre_string)
        return (ft_exit_expander(expander));//free(expnder) seq
    expander->split_pos = ft_split_cmd(expander->pos, ' ');
    if (!expander->split_pos)
        return (ft_exit_expander(expander));//free(epander->pre_string) seq
        
    

    
    if (expander->split_pos[0][ft_strlen(expander->split_pos[0]) - 1] == '"')
    {
        expander->split_pos[0][ft_strlen(expander->split_pos[0]) - 1] = '\0';
        flag = 1;
    }
    if (!(fill_dollar_sign(expander->split_pos, type)))
        return (ft_exit_expander(expander));
    if (flag == 1)
    {
        expander->temp = ft_strjoin(expander->split_pos[0], "\"");
        if (!expander->temp)
            return (ft_exit_expander(expander));
        free(expander->split_pos[0]);
        expander->split_pos[0] = expander->temp;
    }
    expander->last_string = collect_string(expander);
    if (!expander->last_string)
        return (ft_exit_expander(expander));
    free(cmds[n]);
    cmds[n] = expander->last_string;
    free(expander);
    printf("dollar sign:%s\n", cmds[n]);
    return (SUCCESS);
}
