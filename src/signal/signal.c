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

void	sig_prompt_handler(int sig, siginfo_t *info, void *uap)
{
    (void) info;
    (void) uap;

    if (sig == SIGINT)
    {
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_cmd_handler(int sig, siginfo_t *info, void *uap)
{
	(void) info;
	(void) uap;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	init_prompt_sigaction(void)
{
	struct sigaction sact;
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, 0, &term);
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = sig_prompt_handler;
	sigaction(SIGINT, &sact, NULL);
	return (0);
}

int	init_cmd_sigaction(void)
{
	struct sigaction sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = sig_cmd_handler;
	sigaction(SIGINT, &sact, NULL);
	sigaction(SIGQUIT, &sact, NULL);
	return (0);
}
