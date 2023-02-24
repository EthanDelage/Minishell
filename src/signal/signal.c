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

void	sig_handler_prompt(int sig)
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

void	sig_handler_cmd_fork(int sig)
{
	if (sig == SIGINT)
		exit(130);
	else if (sig == SIGQUIT)
		exit(131);
}

void	sig_handler_cmd(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_return_value = 130;
	}
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_return_value = 131;
	}
}

void	sig_handler_here_doc(int sig)
{
	(void) sig;
}

void	sig_handler_here_doc_fork(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(130);
	}
}

int	init_sigaction(void (*sig_handler)(int))
{
	struct sigaction	sact;

	if (sigemptyset(&sact.sa_mask) == -1)
		return (FAILURE);
	sact.sa_handler = sig_handler;
	sact.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sact, NULL) == -1)
		return (FAILURE);
	if (sigaction(SIGQUIT, &sact, NULL) == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	sig_ignore(void)
{

	signal(SIGINT, SIG_IGN);
	if (errno)
		return (FAILURE);
	signal(SIGQUIT, SIG_IGN);
	if (errno)
		return (FAILURE);
	return (SUCCESS);
}
