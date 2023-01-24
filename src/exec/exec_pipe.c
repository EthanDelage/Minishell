/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:45:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/24 17:45:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"
#include "token.h"
#include "router.h"
#include <wait.h>

extern int	g_return_value;

int	exec_pipe(t_token *head, t_hashtable *envp_dict, int fd_stdin, int fd_stdout)
{
	pid_t	pid;
	int		save_stdin;
	int		save_stdout;
	int		pipe_fd[2];

	if (head->next && head->next->type == PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (-1);
		save_stdout = dup(fd_stdout);
		if (save_stdout == -1)
			return (-1);
		if (dup2(pipe_fd[WRITE], fd_stdout) == -1)
			return (-1);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		return (cmd_router(head->cmd_stack, envp_dict));
	else
	{
		waitpid(pid, &g_return_value, 0);
		g_return_value = WEXITSTATUS(g_return_value);
		if (head->next && head->next->type == PIPE)
		{
			if (close(pipe_fd[WRITE]) == -1)
				return (-1);
			if (dup2(save_stdout, fd_stdout) == -1)
				return (-1);
			save_stdin = dup(fd_stdin);
			if (save_stdin == -1)
				return (-1);
			if (dup2(pipe_fd[READ], fd_stdin) == -1)
				return (-1);
			if (exec_pipe(head->next->next, envp_dict, pipe_fd[READ], save_stdout))
				return (-1);
			if (close(pipe_fd[READ]) == -1)
				return (-1);
			if (dup2(save_stdin, fd_stdin) == -1)
				return (-1);
		}
	}
	return (0);
}
