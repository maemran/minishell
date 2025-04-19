/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:01:02 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:34:46 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*here_doc3(char *buffer_res, char *buffer, int file, int *space)
{
	if (is_space(buffer))
		free(space);
	free(buffer);
	buffer = ft_strjoin(buffer_res, "\n");
	if (!buffer)
		return (NULL);
	ft_putstr_fd(buffer, file);
	free(buffer_res);
	return (buffer);
}

char	*here_doc2(int file, char *buffer, t_mini_shell *data)
{
	char	*buffer_res;
	int		*space;
	char	**arr;

	space = NULL;
	if (buffer[0] == '\n')
		return (buffer);
	buffer[ft_strlen(buffer) - 1] = '\0';
	if (is_space(buffer))
		space = spaces(buffer, data);
	arr = ft_split_cmd(buffer, ' ');
	if (arr == NULL)
		return (here_doc_exit(buffer, NULL, space));
	if (!expander(arr, data))
		return (here_doc_exit(buffer, arr, space));
	if (is_space(buffer))
		buffer_res = join_with_num_of_spaces(arr, space, data);
	else
		buffer_res = join_two_d_to_string(arr, " ");
	if (!buffer_res)
		return (here_doc_exit(buffer, arr, space));
	ft_free_tow_d_array(arr);
	return (here_doc3(buffer_res, buffer, file, space));
}

int	here_doc_loop2(char **buffer)
{
	if (g_signum == 2)
		return (2);
	free(*buffer);
	ft_putstr_fd(ARROW, 1);
	*buffer = get_next_line(0);
	if (!(*buffer))
	{
		if (g_signum == 0)
			ft_putstr_fd(UNEXEOF, 2);
		return (2);
	}
	return (SUCCESS);
}

int	here_doc_loop(t_mini_shell *data, char *delimiter, char *buffer, int file)
{
	int	compare;

	compare = 0;
	disable_ctrl_backslash();
	while (compare == FAILURE)
	{
		if (here_doc_loop2(&buffer) == 2)
			break ;
		compare = delmiters_comp(delimiter, buffer);
		if (compare == FAILURE)
		{
			buffer = here_doc2(file, buffer, data);
			if (!buffer)
			{
				restore_ctrl_backslash();
				return (FAILURE);
			}
		}
	}
	if (buffer)
		free(buffer);
	restore_ctrl_backslash();
	return (SUCCESS);
}

int	here_doc(t_mini_shell *data, char *delimiter)
{
	int		file;
	char	*buffer;

	file = open("buffer.txt", O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 0666);
	buffer = ft_strdup("\n");
	if (!here_doc_loop(data, delimiter, buffer, file))
	{
		close(file);
		return (FAILURE);
	}
	close(file);
	if (g_signum == 2)
	{
		unlink("buffer.txt");
		return (FAILURE);
	}
	data->here_doc_file = open("buffer.txt", O_RDONLY);
	return (SUCCESS);
}
