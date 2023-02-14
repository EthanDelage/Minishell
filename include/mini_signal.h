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
# include <signal.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/wait.h>
# include <termios.h>

#define E_SIGINT 1024

int	init_sigaction(void);
int empty_sigaction(void);
struct termios init_termios(void);

#endif
