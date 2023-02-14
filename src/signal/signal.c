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

static void sig_handler(int sig)
{
	pid_t	pid;
	int		exit_status;

	if (errno == EINTR)
		errno = 0;
	pid = waitpid(-1, &exit_status, 0);
	if (errno == ECHILD)
	{
		pid = -1;
		errno = 0;
	}
	if (exit_status == E_SIGINT || WEXITSTATUS(exit_status) == 130 || WTERMSIG(exit_status) % 16 == 0)
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

static void sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(130);
}

int	init_sigaction(void)
{
	struct sigaction sact;

	if (sigemptyset(&sact.sa_mask) == -1)
		return (FAILURE);
	sact.sa_handler = sig_handler;
	if (sigaction(SIGINT, &sact, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sact, NULL) == -1)
		return (-1);
	return (0);
}

int init_sigaction_heredoc(void)
{
	struct sigaction sact;

	if (sigemptyset(&sact.sa_mask) == -1)
		return (FAILURE);
	sact.sa_handler = sig_handler_heredoc;
	if (sigaction(SIGINT, &sact, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sact, NULL) == -1)
		return (-1);
	return (0);
}