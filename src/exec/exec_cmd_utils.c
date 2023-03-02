/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:19:00 by edelage           #+#    #+#             */
/*   Updated: 2023/02/25 17:19:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "exec.h"

void	reset_stdio(int fd_save[2])
{
	if (fd_save[READ] != -1 && fd_save[READ] != STDIN_FILENO)
		if (dup2_fd(fd_save[READ], STDIN_FILENO) == EXIT_FAILURE)
			return ;
	if (fd_save[WRITE] != -1 && fd_save[WRITE] != STDOUT_FILENO)
		if (dup2_fd(fd_save[WRITE], STDOUT_FILENO) == EXIT_FAILURE)
			return ;
}
