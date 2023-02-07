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
		return ;
	}
	printf("test\n");
	printf("%d\n", sig);
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
		return ;
	}
	printf("test\n");
	printf("%d\n", sig);
}

void	init_sigaction(void (*handler) (int, siginfo_t *, void *))
{
	struct sigaction sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = handler;
	sigaction(SIGINT, &sact, NULL);
}