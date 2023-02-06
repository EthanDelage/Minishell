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

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include "libft.h"

void	init_sigaction(void (*handler) (int, siginfo_t *, void *));
void	sig_prompt_handler(int sig, siginfo_t *info, void *uap);
void	sig_cmd_handler(int sig, siginfo_t *info, void *uap);

#endif
