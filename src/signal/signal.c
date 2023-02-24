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

void	sig_handler_cmd(int sig)
{
	(void) sig;
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

//static void	handle_prompt(int sig, pid_t pid);
//
//static void	sig_handler(int sig)
//{
//	pid_t	pid;
//	int		exit_status;
//
//	if (errno == EINTR)
//		errno = 0;
//	pid = waitpid(-1, &exit_status, 0);
//	if (errno == ECHILD)
//	{
//		pid = -1;
//		errno = 0;
//	}
//	if (exit_status == E_SIGINT || WEXITSTATUS(exit_status) == 130
//		|| WTERMSIG(exit_status) % 16 == 0)
//		return ;
//	handle_prompt(sig, pid);
//}
//
//static void	sig_handler_heredoc(int sig)
//{
//	if (sig == SIGINT)
//	{
//		printf("\n");
//		exit(130);
//	}
//}
//
//static void	handle_prompt(int sig, pid_t pid)
//{
//	if (pid == -1)
//	{
//		if (sig == SIGINT)
//		{
//			printf("\n");
//			rl_on_new_line();
//			rl_replace_line("", 0);
//			rl_redisplay();
//			g_return_value = 130;
//		}
//	}
//	else
//	{
//		if (sig == SIGINT)
//		{
//			printf("\n");
//			g_return_value = 130;
//		}
//		else if (sig == SIGQUIT)
//		{
//			printf("Quit (core dumped)\n");
//			g_return_value = 131;
//		}
//	}
//}
//
//int	init_sigaction(void)
//{
//	struct sigaction	sact;
//
//	if (sigemptyset(&sact.sa_mask) == -1)
//		return (FAILURE);
//	sact.sa_handler = sig_handler;
//	if (sigaction(SIGINT, &sact, NULL) == -1)
//		return (FAILURE);
//	if (sigaction(SIGQUIT, &sact, NULL) == -1)
//		return (FAILURE);
//	return (SUCCESS);
//}
//
//int	init_sigaction_heredoc(void)
//{
//	struct sigaction	sact;
//
//	if (sigemptyset(&sact.sa_mask) == -1)
//		return (FAILURE);
//	sact.sa_handler = sig_handler_heredoc;
//	if (sigaction(SIGINT, &sact, NULL) == -1)
//		return (FAILURE);
//	if (sigaction(SIGQUIT, &sact, NULL) == -1)
//		return (FAILURE);
//	return (SUCCESS);
//}
