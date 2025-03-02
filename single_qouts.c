/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_qouts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:22:28 by maemran           #+#    #+#             */
/*   Updated: 2025/03/01 02:23:59 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*OK*/
char    *modify_pipe(void)
{
    char    *string;

    string = ft_strdup("\"|\"");
    if (!string)
        return (NULL);
    return (string);
}
/*OK*/
char    *pipe_check(char *string)//it's mybe give a leaks
{
    char    *str;
    char    *last;
    char    **last_string;
    int flag;

    flag = 0;
    if (!string)
        return (NULL);
    str = ft_strchr(string, '|');
    if(str)
    {
        if (string[0] == '|' && string[1] == '\0')
            return (modify_pipe());
        if (string[ft_strlen(string) - 1] == '|')
            flag = 1;
        if (string[0] == '|')
            flag = 2;
        last_string =  ft_split_cmd(string, '|');
        if (!last_string)
            return (NULL);
        str = join_two_d_to_string(last_string, modify_pipe());
        if (!str)
        {
            ft_free_tow_d_array(last_string);
            return (NULL);
        }
        if (flag > 0)
        {
            if (flag == 1 || flag == 2) 
                last = ft_strjoin(str, modify_pipe());
            if (flag == 2)
                last = ft_strjoin(modify_pipe(), str);
            if (!last)
            {
                ft_free_tow_d_array(last_string);
                free(str);
                return (NULL);
            }
            free(str);
            str = last;
        }
        ft_free_tow_d_array(last_string);
    }
    else if (!str)
        return (ft_strdup(string));//
    return (str);
}
/*OK*/
int    single_qouts_check2(t_expander *expander)
{
    int    i;
    int   flag;

    i = 0;
    flag = 0;
    while (expander->pre_string[i])
    {
        if (expander->pre_string[i] == '"')
            flag= 1;
        i++;
    }
    i = 1;
    expander->pos = ft_strrchr(expander->pos, '\'');
    while (expander->pos[i])
    {
        if (expander->pos[i] == '"')
            flag = 2;
        i++;
    }
    return (flag);
}
/*OK*/
int single_qouts_check(char *split_cmd)
{
    t_expander *expander;
    int     flag;
    int     offset;

    flag = 0;
    expander = malloc(sizeof(t_expander));
    if (!expander)
        return (2);
    expander->pos = ft_strchr(split_cmd, '\'');
    offset = expander->pos - split_cmd;
    expander->pre_string = malloc(offset + 1);
    if (!expander->pre_string)
    {
        free(expander);
        return(2);
    }
    expander->pre_string = ft_strncpy(expander->pre_string, split_cmd, offset);
    expander->pre_string[offset] = '\0';
    flag = single_qouts_check2(expander);
    free(expander->pre_string);
    free(expander);
    if (flag == 2 || flag == 1)
        return (0);
    return(1);
}
/*OK*/
int    single_qouts(char *split_cmd, char **string_cmd, int n)
{
    t_expander *expander;
    char    *temp;
    
    if (single_qouts_check(split_cmd) == 0)
        return (SUCCESS);
    else if (single_qouts_check(split_cmd) == 2)
        return (FAILURE);
    if ((split_cmd[0] == '\'' && split_cmd[1] == '\0') 
        || (split_cmd[0] == '\'' && split_cmd[ft_strlen(split_cmd) - 1] != '\''))
    {
        string_cmd[n] = ft_strdup("");
        if (!string_cmd[n])
            return (FAILURE);
        return (SUCCESS);
    }
    expander = malloc (sizeof(t_expander));
    if (!expander)
        return (FAILURE);
    ft_initialize_expander(expander);
    expander->pos = ft_strchr(split_cmd, '\'');
    expander->pre_string = ft_pre_string(split_cmd, expander->pos);
    if (!expander->pre_string)
        return (ft_exit_expander(expander));
    expander->split_pos = ft_split_cmd(expander->pos, ' ');
    if (!expander->split_pos)
        return (ft_exit_expander(expander));
    temp = ft_strtrim(expander->split_pos[0], "'");
    expander->temp = ft_strdup(temp);
    free(temp);
    if (!expander->temp)
        return (ft_exit_expander(expander));
    free(expander->split_pos[0]);
    expander->split_pos[0] = expander->temp;
    expander->temp = NULL;
    temp = collect_string(expander);
    expander->last_string = pipe_check(temp);
    free(temp);
    if (!expander->last_string)
        return (ft_exit_expander(expander));
    free (string_cmd[n]);
    string_cmd[n] = expander->last_string;
    printf("single:%s\n", string_cmd[n]);
    free(expander);
    return (SUCCESS);
}
