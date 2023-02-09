/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:26:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/02/04 16:26:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mini_signal.h"

extern unsigned char g_return_value;

void sig_handler(int sig)
{
	pid_t	pid;
	int		exit_status;

	pid = waitpid(-1, &exit_status, 0);
	if (exit_status == E_SIGINT)
		return ;
	if (pid == -1)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_return_value = 130;
		}
	}
	else
	{
		if (sig == SIGINT)
		{
			printf("\n");
			g_return_value = 130;
		}
		else if (sig == SIGQUIT)
		{
			printf("Quit (core dumped)\n");
			g_return_value = 131;
		}
	}
}

int	init_sigaction(void)
{
	struct sigaction sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = sig_handler;
	sigaction(SIGINT, &sact, NULL);
	sigaction(SIGQUIT, &sact, NULL);
	return (0);
}

struct termios init_termios(void)
{
	struct termios old_term;
	struct termios new_term;

	if (tcgetattr(STDIN_FILENO, &old_term) == -1)
		return old_term;
	new_term = old_term;
	new_term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, 0, &new_term);
	return (old_term);
}
