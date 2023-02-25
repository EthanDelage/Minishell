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
