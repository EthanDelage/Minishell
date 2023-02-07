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
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <termio.h>

int	init_prompt_sigaction(void);
int init_cmd_sigaction(void);

#endif
