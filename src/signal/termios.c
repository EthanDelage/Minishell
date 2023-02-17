/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:31:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/02/14 21:31:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mini_signal.h"

int termios_save(struct termios *termios_save)
{
	if (isatty(STDERR_FILENO) == 0)
		return (0);
	return (tcgetattr(STDERR_FILENO, termios_save));
}

int termios_restore(const struct termios termios_save)
{
	if (isatty(STDERR_FILENO) == 0)
		return (0);
	return (tcsetattr(STDERR_FILENO, 0, &termios_save));
}

int termios_disable_vquit(void)
{
	struct termios	termios_tmp;

	if (isatty(STDERR_FILENO) == 0)
		return (0);
	if (tcgetattr(STDERR_FILENO, &termios_tmp) == -1)
		return (-1);
	termios_tmp.c_cc[VQUIT] = 0;
	return (tcsetattr(STDERR_FILENO, 0, &termios_tmp));
}