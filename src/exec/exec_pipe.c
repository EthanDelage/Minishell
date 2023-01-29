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
#include "redirect.h"
#include "replace.h"

extern unsigned char	g_return_value;

static int	init_pipe(t_token *head, int fd_pipe[2]);

int	exec_pipe(t_token *token, t_hashtable *envp_dict, int fd_pipe_in)
{
	int	return_val;
	int	pid;
	int	fd_io[2];
	int	fd_pipe[2];

	if (replace(envp_dict, token->cmd_stack) == 1)
		return (1);
	if (redirect_open(envp_dict, token->cmd_stack) == EXIT_FAILURE)
		return (-1);
	if (init_pipe(token, fd_pipe) != 0)
		return (-1);
	fd_io[WRITE] = redirect_get_output_fd(token->cmd_stack);
	fd_io[READ] = redirect_get_input_fd(token->cmd_stack);
	if (fd_io[READ] == -1 && fd_pipe_in == -1)
		fd_io[READ] = STDIN_FILENO;
	else if (fd_io[READ] == -1)
		fd_io[READ] = fd_pipe_in;
	if (fd_io[WRITE] == -1 && fd_pipe[WRITE] == -1)
		fd_io[WRITE] = STDOUT_FILENO;
	else if (fd_io[WRITE] == -1)
		fd_io[WRITE] = fd_pipe[WRITE];
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		errno = 0;
		if (token && token->next && token->next->type == PIPE)
			close(fd_pipe[READ]);
		if (fd_io[WRITE] != STDOUT_FILENO)
		{
			dup2(fd_io[WRITE], STDOUT_FILENO);
			close(fd_io[WRITE]);
		}
		if (fd_io[READ] != STDIN_FILENO)
		{
			dup2(fd_io[READ], STDIN_FILENO);
			close(fd_io[READ]);
		}
		exit(cmd_router(token->cmd_stack, envp_dict));
	}
	else
	{
		if (token && token->next && token->next->type == PIPE)
		{
			close(fd_pipe[WRITE]);
			if (exec_pipe(token->next->next, envp_dict, fd_pipe[READ]) == -1)
				return (-1);
			close(fd_pipe[READ]);
		}
		waitpid(pid, &return_val, 0);
		g_return_value = WEXITSTATUS(return_val);
	}
	redirect_close(token->cmd_stack);
	return (0);
}

static int	init_pipe(t_token *head, int fd_pipe[2])
{
	if (head && head->next && head->next->type == PIPE)
	{
		if (pipe(fd_pipe) == -1)
			return (errno);
	}
	else
		fd_pipe[WRITE] = -1;
	return (0);
}
