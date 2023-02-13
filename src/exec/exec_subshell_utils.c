/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:44:00 by edelage           #+#    #+#             */
/*   Updated: 2023/02/13 13:44:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "exec.h"

int	exec_subshell_fork(t_hashtable *envp_dict, t_token *head, int fd_io[2])
{
	exec_fork_set_fd_io(fd_io);
	exec(head->next, envp_dict);
	return (g_return_value);
}
