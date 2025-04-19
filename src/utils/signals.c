/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:28:33 by maemran           #+#    #+#             */
/*   Updated: 2025/04/19 03:37:50 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	disable_ctrl_backslash(void)
{
	struct termios	term;

	signal(SIGQUIT, SIG_IGN);
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

void	restore_ctrl_backslash(void)
{
	struct termios	term;

	dup2(2, 0);
	tcgetattr(0, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\b\b");
		g_signum = SIGINT;
		close(0);
	}
}

int	see_sig(void)
{
	struct sigaction	sa;
	struct sigaction	sq;

	sigemptyset(&sa.sa_mask);
	sigemptyset(&sq.sa_mask);
	sa.sa_handler = sigint_handler;
	sq.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sq.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGQUIT, &sq, NULL)
		== -1)
		return (FAILURE);
	return (SUCCESS);
}
