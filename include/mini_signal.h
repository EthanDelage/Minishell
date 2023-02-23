/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:28:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/02/04 16:28:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <termios.h>
# include "minishell.h"

# define E_SIGINT 1024

int	init_sigaction(void);
int	init_sigaction_heredoc(void);
int	termios_save(struct termios *termios_save);
int	termios_restore(struct termios termios_save);
int	termios_disable_vquit(void);

#endif
