/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:33:35 by salshaha          #+#    #+#             */
/*   Updated: 2025/04/19 03:59:35 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>

# define SUCCESS 1
# define FAILURE 0
# define PROMPT \
	"\022\033[1;31m➜  \
\022\033[1;36mminishell \022\033[1;31m»\022\033[0m "
# define ERORR_MSG "\033[1;31mminishell:\033[0m "
# define UNEXEOF \
	"\b\b\033[1;36m> \033[0m\n\033[1;31mminishell: \
\033[0msyntax error: unexpected end of file\n"
# define ARROW "\033[1;36m> \033[0m"
# define ARR_SIG "\033[1;36m>\033[0m ^C\n"
# define SIG "^C\n"

extern int		g_signum;

typedef struct s_expander
{
	char		**split_pos;
	char		**tokens;
	char		*pre_string;
	char		*last_string;
	char		*temp;
	char		*pos;
	int			i;
	int			count;
}				t_expander;

typedef struct s_mini_shell
{
	char		**env;
	char		*oldpwd;
	char		*shlvl;
	int			syntax_error;
	int			pipe;
	char		**sorted_env;
	char		*underscore;
	int			here_doc_file;
	int			here_with_error;
	int			terminate_process;
	int			before;
	int			exit_status;
	int			save_exit_status;
	int			exit_status_value;
	int			delimiter_num;
	int			saved_stdin;
	int			saved_exit;
	int			here_doc_num;
}				t_mini_shell;

typedef struct s_tokenizer
{
	char		*infile;
	char		*delimiter;
	char		**delimiters;
	char		**array;
	char		*str;
	char		*outfile;
	char		**out_files;
	char		*out;
	char		*cmd;
	char		*cmd_args;
	char		*temp1;
	char		*temp2;
	int			syntax_error;
	int			here_doc;
	int			append;
	int			fd_in;
	int			fd_out;
	int			builtin;
	int			*outs;
	int			flag;
	int			flag2;
	int			flag3;
	int			i;
	int			j;
	int			here_red;
	int			fd_num;
}				t_tokenizer;

typedef struct s_executer
{
	char		**paths;
	char		**command_args;
	char		*path;
	char		*command;
	long long	code;
	int			*fds;
	int			saved_stdin;
	int			saved_stdout;
	int			size;
	int			id;
	int			i;
	int			x;
	int			j;
	int			h_i;
	int			h_j;
	int			h_k;
	int			h_flag;
	int			counter;
	int			**fd;
}				t_executer;

t_tokenizer		**tokenizer_prepration(char *input, t_mini_shell *data);
t_tokenizer		**join_commands(t_tokenizer **commands,
					t_tokenizer **new_commands);
t_tokenizer		**exit_commands(t_tokenizer **cmds1, t_tokenizer **cmds2);
t_tokenizer		**clear_command(t_tokenizer **commands);
t_tokenizer		**add_commands(t_tokenizer **commands, t_mini_shell *data);
t_tokenizer		**free_tokenizer(t_tokenizer **commands, char **split);
t_tokenizer		*ft_tokenizer(char *string, t_mini_shell *data);
t_tokenizer		*dup_commands(t_tokenizer *command);
t_tokenizer		*free_command(t_tokenizer *commands);
void			free_commands(t_tokenizer **commands);
void			free_arrays(t_tokenizer *commands);
void			delimiters_type(char *str, int *i);
char			**tokenizer_checks(char *input, t_mini_shell *data);
char			**tokens_for_tokenizer(char *str);
char			**fill_tokens(t_expander *expander, char *str);
int				dup_commands_check1(t_tokenizer *command, t_tokenizer *new);
int				dup_commands_check2(t_tokenizer *command, t_tokenizer *new);
int				join_commands_loop(int *i, t_tokenizer **new,
					t_tokenizer **new_commands);
int				cmd_and_args(t_tokenizer *commands);
int				red_out_check(t_tokenizer *commands);
int				red_in_check2(t_tokenizer *commands, t_mini_shell *data);
int				red_in_check1(t_tokenizer *commands);
int				redirection_check(char **array, int i);
int				initialize_here_doc(t_tokenizer *commands, int *flag,
					char *array);
int				multi_out_file(t_tokenizer *commands, int *flag, char *array);
int				ft_initialize_tokenizer(t_tokenizer *commands);
int				multi_pipes(char *input);
int				multi_pipes_loops(int *i, char *input);
int				pipe_between_spaces(char *input);
int				multi_infiles(t_tokenizer **commands);
int				fill_input(t_tokenizer *commands, t_mini_shell *data);
int				tokinizer_loop(t_tokenizer *commands, t_mini_shell *data);
int				tokinizer_loop2(t_tokenizer *commands);
int				count_token(char *str);
int				delimiter(char c);
int				fill_outfiles_ands_delimiters(t_tokenizer *commands,
					t_mini_shell *data);
int				input_file_check(t_tokenizer *command);

void			print_echo_args(char **str, int i);
void			env(t_mini_shell *data);
void			error_msg(char *str1, char *str2);
void			pubble_sort(t_mini_shell *data);
char			**echo1(char *string, t_mini_shell *data);
char			**unset2(char *string, char **new_env, t_mini_shell *data);
char			**join_export(char **sorted_env);
char			*cd1(t_mini_shell *data, char *full_cmd, char *path);
char			*cd2(t_mini_shell *data, char *str1);
char			*var_before_equal(char *string);
char			*modify_path2(t_mini_shell *data);
char			*ft_getenv(t_mini_shell *data, char *var);
char			*free_all(char *str1, char *str2, char **str3, char **str4);
char			*export_string_check(char *string, t_mini_shell *data);
int				cd3(char *path, t_mini_shell *data);
int				cd(char *path, t_mini_shell *data, char *full_cmd);
int				unset(char *string, t_mini_shell *data);
int				unset_string(char *string, t_mini_shell *data);
int				pwd(void);
int				dash_n_check(char **str, int i);
int				echo_with_n(char **str);
int				echo(char *string, t_mini_shell *data);
int				modify_path(t_mini_shell *data);
int				modify_shell(t_mini_shell *data);
int				env_copy(char **env, t_mini_shell *data);
int				find_env_var(char *string, t_mini_shell *data, int flag);
int				sort_export(t_mini_shell *data);
int				export(char *string, t_mini_shell *data);
int				export_string(char *string, t_mini_shell *data);
int				new_env(char *str, char *temp, t_mini_shell *data);
int				shell_level(t_mini_shell *data);

t_tokenizer		**check_before_executer(t_tokenizer **commands,
					t_mini_shell *data);
t_tokenizer		**exit_executer(t_tokenizer **commmands);
void			ft_close(t_tokenizer *command, t_tokenizer **commands,
					t_executer *exe);
int				is_directory(char *path);
int				open_redirection_out(t_tokenizer *command);
int				open_append_out(t_tokenizer *command);
int				syntax_error_check(t_tokenizer **commands);
int				no_command_check(t_tokenizer **commands);
int				no_command_check(t_tokenizer **commands);
void			exit_status(t_mini_shell *data, t_tokenizer **commands,
					t_executer *exe);
void			free_exe(t_executer *exe);
void			close_parent_fds(t_executer *exe);
void			free_child_process(t_mini_shell *data, t_tokenizer **commands,
					t_executer *exe, int status);
void			command_found_checks(t_tokenizer *commands, t_executer *exe,
					t_mini_shell *data, t_tokenizer **cmds);
void			execute2(t_tokenizer *commands, t_mini_shell *data,
					t_executer *exe, t_tokenizer **cmds);
char			**delimiters(t_tokenizer **commands, t_mini_shell *data);
int				exit_command2(char **args, t_executer *exe, t_mini_shell *data,
					t_tokenizer **commands);
int				exit_command(char *str, t_executer *exe, t_mini_shell *data,
					t_tokenizer **commands);
int				executer_loop(t_mini_shell *data, t_tokenizer **commands,
					t_executer *exe);
int				executer_loop2(t_mini_shell *data, t_tokenizer **commands,
					t_executer *exe);
int				initialize_exe(t_executer *exe, t_mini_shell *data,
					t_tokenizer **commands);
int				redirection(t_tokenizer *command, t_mini_shell *data,
					t_executer *exe);
int				export_underscore(t_mini_shell *data);
int				underscore(t_mini_shell *data, t_tokenizer **commands,
					t_executer *exe);
int				child_process(t_mini_shell *data, t_tokenizer **commands,
					t_executer *exe);
int				paths_and_args(t_tokenizer *commands, t_executer *exe);
int				path_search(t_tokenizer *commands, t_mini_shell *data,
					t_executer *exe);
int				execute(t_tokenizer *commands, t_mini_shell *data,
					t_executer *exe, t_tokenizer **cmds);
int				redirection2(t_tokenizer *command, t_mini_shell *data,
					t_executer *exe);
int				executer(t_mini_shell *data, t_tokenizer **commands);
int				executer2(t_mini_shell *data, t_tokenizer **commands,
					t_executer *exe);
int				size_of_commands(t_tokenizer **commands);
int				quotes_search(char *str);
int				remove_quotes(char **array, t_mini_shell *data);
int				relative_absolute_path(t_tokenizer *commands,
					t_mini_shell *data);
int				free_param(t_executer *exe, char *str);
int				prepare_here_doc(t_mini_shell *data, t_tokenizer **commands,
					t_executer *exe);
int				init_fds(t_executer *exe, t_tokenizer **commands);
int				count_num_of_here_docs(t_tokenizer **commands);
int				num_of_delimiters(t_tokenizer **commands, t_mini_shell *data);
int				check_before_executer2(t_tokenizer ***commands,
					t_mini_shell *data);
int				error_check(t_mini_shell *data);
int				is_here_doc(t_tokenizer **command);
int				built_execution3(t_tokenizer *commands, t_mini_shell *data);
int				pipes_init(t_executer *exe, int size);
void			free_pipes(t_executer *exe);
int				is_exit(char *str);
int				is_biltin(char *cmd);
int				built_execution(t_tokenizer *command, t_mini_shell *data,
					t_executer *exe);
void			close_here_doc_fds(t_executer *exe, t_tokenizer **commands);
int				syntax_error_for_red(t_tokenizer **commands);

t_expander		*free_struct(t_expander *expander);
t_expander		*dollar_sign2(char *split_cmd, int type, t_mini_shell *data);
void			count_tokens_qouts(t_expander *tokens, char *str);
void			count_tokens_dollar(t_expander *tokens, char *str);
void			count_tokens_others(t_expander *tokens, char *str);
void			ft_initialize_expander(t_expander *expander);
char			**dollar_inside_single2(char *string, int type,
					t_mini_shell *data);
char			**tokens(char *str);
char			**ft_exit_tokens(t_expander *tokens, char **result);
char			*tokens2(t_expander *tokens, char *str, char **result);
char			*tokens_others2(char *str, t_expander *tokens, char **result);
char			*tokens_others(char *str, t_expander *tokens, char **result);
char			*tokens_dollar(char *str, t_expander *tokens, char **result);
char			*tokens_qouts(char *str, t_expander *tokens, char **result);
char			*string_type(t_expander *tokens, char *str);
char			*toknes_join(char **cmds);
char			*collect_string(t_expander *expander);
char			*ft_pre_string(char *split_cmd, char *pos);
char			*fill_dollar_sign2(char **split_pos, int type,
					t_mini_shell *data);
char			*num_after_dollar_sign(char *str);
char			*dollar_sgin_variable_check(char *var_out);
char			*dollar_sign_check2(char **cmds, int n, t_mini_shell *data);
char			*dollar_sign_check(char **cmds, int n);
char			*double_qouts_expand(char *split_cmd, t_mini_shell *data);
char			*double_qouts2(char *split_cmd, int *space, char **split_input,
					t_mini_shell *data);
char			*home_sign(char *split_cmd, char **string_cmd, int n,
					t_mini_shell *data);
char			*expand(char *split_cmd, t_mini_shell *data);
char			*join_two_d_to_string(char **cmds, char *c);
char			*add_single(char *str, int type);
char			*mem_alloc(char *str, int type, int n);
char			*add_single_with_dollar(char *str, int type);
char			*dollar_inside_single3(char **array, int n, int flag,
					t_mini_shell *data);
char			*dollar_with_single3(char **array, int n, int flag,
					t_mini_shell *data);
char			*join_with_num_of_spaces(char **cmds, int *spaces,
					t_mini_shell *data);
char			*join_with_num_of_spaces2(char **cmds, int *spaces,
					char *string);
char			*join_spaces_before(char **cmds, int *spaces);
char			*join_spaces_loop(int *i, char **cmds, int *spaces);
char			*join_spaces(char *string, int n);
int				*spaces(char *str, t_mini_shell *data);
int				*fill_spaces(int *spaces, char *str, int *i, int *j);
int				dollar_sign3(int type, t_mini_shell *data,
					t_expander *expander);
int				count_tokens(char *str, t_expander *tokens);
int				fill_dollar_sign(char **split_pos, int type,
					t_mini_shell *data);
int				ft_exit_expander(t_expander *expander, char *str);
int				is_only_one_space(char *str);
int				dollar_sign(char **cmds, int n, int type, t_mini_shell *data);
int				double_qouts_loop(char **cmds, t_mini_shell *data);
int				double_qouts_check(char *split_cmd, char **string_cmd, int n);
int				double_qouts(char *split_cmd, char **string_cmd, int n,
					t_mini_shell *data);
int				expander(char **split_cmd, t_mini_shell *data);
int				modify_input(char *input, t_mini_shell *data);
int				signals_on_prompt(t_mini_shell *data, int *count);
int				sapce_inside_qouts(char *string, char c);
int				prepare_before_expand(t_mini_shell *data, char **str);
int				expand_tokenizer_loop(t_tokenizer **commands,
					t_mini_shell *data, int *i);
int				expand_tokenizer(t_tokenizer **commands, t_mini_shell *data);
int				ft_exit_double_qouts(char **array, int *spaces);
int				dollar_inside_single(char **array, int n, t_mini_shell *data);
int				dollar_with_single(char **array, int n, t_mini_shell *data);
int				single_qouts(char *split_cmd, char **string_cmd, int n);
int				single_qouts2(char *split_cmd, char **string_cmd, int n,
					t_expander *expander);
int				single_qouts_check(char *split_cmd);
int				single_qouts_check2(t_expander *expander);
int				num_of_spaces(char *str, t_mini_shell *data);
int				is_space(char *str);
int				is_delimiter(char c);
int				odd_num_qouts(char *input);

t_mini_shell	*prepare(t_mini_shell *data, char **env, int argc, char **argv);
void			ft_initialize_minishell(t_mini_shell *data);
void			free_minishell_struct(t_mini_shell *data);
void			main_exit(t_mini_shell *data);
void			mini_loop(int *count, char *buffer, t_mini_shell *data);
int				ft_free_all(char *str1, char *str2, char **str3, char **str4);
int				is_only_spaces(char *str);

void			sigint_handler(int signal);
void			restore_ctrl_backslash(void);
void			disable_ctrl_backslash(void);
int				see_sig(void);
int				signals_on_prompt(t_mini_shell *data, int *count);

void			fill_fds(t_tokenizer **commands, t_executer *exe,
					t_mini_shell *data);
char			*here_doc_exit(char *str, char **array, int *spaces);
char			*here_doc2(int file, char *buffer, t_mini_shell *data);
char			*here_doc3(char *buffer_res, char *buffer, int file,
					int *space);
int				delmiters_comp(char *delimiter, char *buffer);
int				here_doc_delimiters(char **delimiters, t_mini_shell *data,
					t_executer *exe, t_tokenizer **commands);
int				here_doc(t_mini_shell *data, char *delimiter);
int				here_doc_loop(t_mini_shell *data, char *delimiter, char *buffer,
					int file);
int				here_doc_loop2(char **buffer);
void			type_of_exit(int exit_status, t_mini_shell *data,
					t_executer *exe, t_tokenizer **cmds);

#endif