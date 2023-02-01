/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:36:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/01/28 18:36:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXEC_H
# define EXEC_H

# include "token.h"
# include "redirect.h"
# include "envp.h"
# include "router.h"
# include "replace.h"
# include <wait.h>

/* ---------------	EXEC FUNCTIONS	--------------- */

t_token	*exec_cmd(t_token *head, t_hashtable *envp_dict);

/* ---------------	EXEC_UTILS FUNCTIONS	--------------- */

int		exec_set_fd_io(t_cmd_token *head, int fd_io[2], t_hashtable *envp_dict);
int		dup2_save_fd(int new_fd, int old_fd);

#endif
