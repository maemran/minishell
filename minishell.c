/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:02:51 by salshaha          #+#    #+#             */
/*   Updated: 2025/02/20 19:02:51 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*OK*/
char    *home_sign(char *split_cmd, char **string_cmd, int n)
{
    char    *var_out;
    char    *string;

    if (string_cmd[n][1] == '/' || string_cmd[n][1] == '\0')
    {
        var_out = getenv("HOME");
        if(!var_out)
            return (NULL);
        else
            var_out = ft_strdup(var_out);
        if (!var_out)
            return (NULL);
    }
    if (string_cmd[n][1] == '/')
    {
        string = ft_strjoin(var_out, split_cmd + 1);
        free(var_out);
        if (!string)
            return (NULL);
    }
    if (string_cmd[n][1] == '\0')
        string = var_out;
    printf("%s\n", string);
    return(string);
}

/*OK*/
char    *expand(char *split_cmd)
{
    char    **cmds;
    char    *string;
    int    null_check;
    int i;
    
    i = 0;
    cmds = tokens(split_cmd);
    null_check = 1;
    if (!cmds)
        return (NULL);
    while (cmds[i])
    {
        if (cmds[i][0] == '$')
            null_check = dollar_sign(cmds[i], cmds, i, 1);
        else if (cmds[i][0] == '\'')
            null_check = single_qouts(cmds[i], cmds, i);
        else if(cmds[i][0] == '"')
            null_check = double_qouts(cmds[i], cmds, i);
        i++;
    }
    if (!null_check)
        return ((char *)ft_exit_tokens(NULL, cmds));
    string = toknes_join(cmds);
    ft_free_tow_d_array(cmds);
    return (string);
}
/*OK*/
int     expander(char **split_cmd)
{
    int i;
    char *string;

    i = 0;
    while(split_cmd[i])
    {
        if ((split_cmd[i][0] == '~' && split_cmd[i][1] == '\0')
            || (split_cmd[i][0] == '~' && split_cmd[i][1] == '/'))
        {
            string = home_sign(split_cmd[i], split_cmd, i);
            if (!string)
                return (FAILURE);
        }
        else
        {
            string = expand(split_cmd[i]);
            if (!string)
                return (FAILURE);
        }
        free(split_cmd[i]);
        split_cmd[i] = string;
        i++;
    }
    return(SUCCESS);
}
/*OK*/
int    modify_input(char *input)
{
    char **split_cmd;

    split_cmd = ft_split_cmd(input, ' ');
    if (!split_cmd)
        return (FAILURE);
    if (!expander(split_cmd))
    {
        free(input);
        ft_free_tow_d_array(split_cmd);
        return (FAILURE);
    }
    ft_free_tow_d_array(split_cmd);
    // //tokenizer
    // //for test
    // ft_free_tow_d_array(split_cmd);
    // free(input);
    // exit(0);
    // //for test except free_two_d
    return (SUCCESS);
}
    
/*OK*/
int main(int argc, char **argv, char **env)
{
    char    *buffer;

    (void)argv;
    (void)argc;
    (void)env;
    buffer = NULL;
    print_ascii_art();
    while (1)
    {
        buffer = readline("\033[1;31m➜  \033[1;36mminishell \033[1;31m»\033[0m ");
        if (buffer && buffer[0] != '\0')
            add_history(buffer);
        if (!modify_input(buffer))
        {
            //free(buffer);
            ft_putstr_fd("\033[1;31mminishell:\033[0m Out of memory\n", 2);
            exit(1);
        }
    }
}
