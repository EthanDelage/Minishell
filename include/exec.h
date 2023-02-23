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
# include "minishell.h"
# include <wait.h>

/* ---------------	EXEC FUNCTIONS	--------------- */

void	exec(t_token **head, t_hashtable *envp_dict);
t_token	*exec_cmd(t_token *head, t_hashtable *envp_dict);
t_token	*exec_pipe(t_token **head, t_hashtable *envp_dict, int fd_in);
t_token	*exec_subshell(t_token **head, t_hashtable *envp_dict);

/* ---------------	EXEC_UTILS FUNCTIONS	--------------- */

void	exec_fork_set_fd_io(int fd_io[2]);
int		exec_set_fd_io(t_cmd_token *head, int fd_io[2], t_hashtable *envp_dict);
int		exec_pipe_set_fd_io(t_cmd_token *head, int fd_io[2], int fd_out_pipe,
			t_hashtable *envp_dict);
int		dup2_fd(int new_fd, int old_fd);

/* ---------------	EXEC_SUBSHELL_UTILS FUNCTIONS	--------------- */

int		exec_subshell_fork(t_hashtable *envp_dict, t_token **head,
			int fd_io[2]);

/* ---------------	EXEC_PIPE_UTILS FUNCTIONS	--------------- */

pid_t	exec_pipe_subshell(t_token **head, t_hashtable *envp_dict,
			int fd_in, int fd_pipe[2]);
t_token	*get_next_pipe(t_token *head);
t_token	*get_next_cmd(t_token *head);
void	close_pipe(int fd_pipe[2]);

#endif
