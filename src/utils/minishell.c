/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:26:34 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:37:44 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				g_signum = 0;

int	signals_on_prompt(t_mini_shell *data, int *count)
{
	if (g_signum == 2)
	{
		dup2(2, 0);
		g_signum = 0;
		data->save_exit_status = 130;
		data->exit_status = 0;
		if ((*count) == 0)
			printf("\n");
		(*count)++;
		return (FAILURE);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		free_minishell_struct(data);
		rl_clear_history();
		exit(0);
	}
	return (SUCCESS);
}

int	shell_level(t_mini_shell *data)
{
	int		shelvl;
	char	*str;

	if (!getenv("SHLVL"))
		return (SUCCESS);
	shelvl = ft_atoi(getenv("SHLVL"));
	if (!unset("SHLVL", data))
		return (FAILURE);
	shelvl++;
	data->shlvl = ft_itoa(shelvl);
	if (!data->shlvl)
		return (FAILURE);
	str = ft_strjoin("SHLVL=", data->shlvl);
	if (!str)
		return (FAILURE);
	if (!export_string(str, data))
	{
		free(str);
		return (FAILURE);
	}
	free(str);
	free(data->shlvl);
	data->shlvl = NULL;
	return (SUCCESS);
}

t_mini_shell	*prepare(t_mini_shell *data, char **env, int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		error_msg("too many arguments\n", NULL);
		exit(1);
	}
	data = malloc(sizeof(t_mini_shell));
	ft_initialize_minishell(data);
	if (!data)
	{
		ft_putstr_fd("minishell: malloc error\n", 2);
		exit(1);
	}
	if (!env_copy(env, data))
		main_exit(data);
	if (!shell_level(data))
		main_exit(data);
	if (!see_sig())
		main_exit(data);
	print_ascii_art();
	return (data);
}

void	mini_loop(int *count, char *buffer, t_mini_shell *data)
{
	(*count) = 0;
	if (buffer && buffer[0] != '\0'
		&& !is_only_spaces(buffer))
		add_history(buffer);
	if (!modify_input(buffer, data))
	{
		free(buffer);
		rl_clear_history();
		free_minishell_struct(data);
		exit(1);
	}
	if (g_signum == 2)
	{
		dup2(2, 0);
		data->exit_status = 130;
		g_signum = 0;
	}
	data->save_exit_status = data->exit_status;
	data->exit_status = 0;
	free(buffer);
	buffer = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	*data;
	char			*buffer;
	int				count;

	count = 0;
	data = NULL;
	data = prepare(data, env, argc, argv);
	while (1)
	{
		data->here_doc_num = 0;
		buffer = readline(PROMPT);
		if (!buffer)
		{
			if (!signals_on_prompt(data, &count))
				continue ;
		}
		if (buffer[0] == '\0')
		{
			data->save_exit_status = 0;
			data->exit_status = 0;
			free(buffer);
			continue ;
		}
		mini_loop(&count, buffer, data);
	}
}
