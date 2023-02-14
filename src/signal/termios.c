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

struct termios	termios_get(int fd)
{
	struct termios	term;

	if (tcgetattr(fd, &term) == -1)
	{
		perror("minishell: termios");
		return (term);
	}
	return (term);
}

struct termios termios_init_rl(struct termios old_term)
{
	struct termios new_term;

	new_term = old_term;
	new_term.c_cc[VQUIT] = 0;
	if (tcsetattr(STDIN_FILENO, 0, &new_term) == -1)
		perror("minishell: termios");
	return (old_term);
}


struct termios termios_init_heredoc(struct termios old_term)
{
	struct termios new_term;

	new_term = old_term;
	new_term.c_cc[VQUIT] = 0;
	if (tcsetattr(STDIN_FILENO, 0, &new_term) == -1)
		perror("minishell: termios");
	return (old_term);
}
