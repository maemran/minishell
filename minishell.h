/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:33:35 by salshaha          #+#    #+#             */
/*   Updated: 2025/02/20 15:33:35 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct s_expander
{
    char    **split_pos;
    char    *pre_string;
    char    *last_string;
    char    *temp;
    char    *pos;
    int i;
    int count;
}   t_expander;

typedef struct s_shell
{
    char    **env;
}   t_shell;

int     is_only_one_space(char *str);
int      fill_dollar_sign(char **split_pos, int type);
char    *ft_pre_string(char *split_cmd, char *pos);
char    *collect_string(t_expander *expander);
int     dollar_sign(char *split_cmd, char **string_cmd, int n, int type);
int     single_qouts_check2(t_expander *expander);
int     single_qouts_check(char *split_cmd);
int    single_qouts(char *split_cmd, char **string_cmd, int n);
char    *double_qouts_expand(char *split_cmd);
int    double_qouts(char *split_cmd, char **string_cmd, int n);
char    *expand(char *split_cmd);// i want to use this function to expand the "|"
int     expander(char **split_cmd);
char    *join_two_d_to_string(char **cmds, char *c);
char    *modify_pipe(void);
char    *pipe_check(char *string);
void    ft_initialize_expander(t_expander *expander);
int    ft_exit_expander(t_expander *expander);


/*tokens function headers*/
int     is_delimiter(char c);
char    *tokens_qouts(char *str, t_expander *tokens, char **result);
char    *tokens_dollar(char *str ,t_expander *tokens, char **result);
char    *tokens_others(char *str ,t_expander *tokens, char **result);
char    **tokens(char *str);
void    count_tokens_qouts(t_expander *tokens, char *str);
void    count_tokens_dollar(t_expander *tokens, char *str);
void    count_tokens_others(t_expander *tokens, char *str);
int     count_tokens(char *str, t_expander *tokens);
char    *toknes_join(char **cmds);//return NULL
char    **ft_exit_tokens(t_expander *tokens, char **result);
char    *tokens2(t_expander *tokens, char *str, char **result);
/*tokens function headers*/


int delimiter(const char *str, int i);
int count_tokens_l(const char *str);
char **split_string(char *str);

void    env_fun(char **env);
void    pwd(void);
void    cd(char *bath);

#endif