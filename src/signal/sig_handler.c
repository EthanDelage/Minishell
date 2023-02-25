/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:16:00 by edelage           #+#    #+#             */
/*   Updated: 2023/02/25 15:16:00 by edelage          ###   ########lyon.fr   */
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
