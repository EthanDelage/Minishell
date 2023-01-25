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

extern int	g_return_value;

static int	init_pipe(t_token *head, int fd_pipe[2]);

//int	exec_pipe(t_token *token, t_hashtable *envp_dict, int fd_in)
//{
//	pid_t	pid;
//	int		fd_pipe[2];
//	int		fd_io[2];
//	int		save_in;
//
//	redirect_open(token->cmd_stack);
//	init_pipe(token, fd_pipe);
//	fd_io[WRITE] = redirect_get_output_fd(token->cmd_stack);
//	fd_io[READ] = redirect_get_input_fd(token->cmd_stack);
//	if (fd_io[READ] == -1)
//		fd_io[READ] = fd_in;
//	if (fd_io[WRITE] == -1 && fd_pipe[WRITE] == -1)
//		fd_io[WRITE] = STDOUT_FILENO;
//	else if (fd_io[WRITE] == -1)
//		fd_io[WRITE] = fd_pipe[WRITE];
//	printf("%s: I need to read from fd: %d\n", token->cmd_stack->head, fd_io[READ]);
//	printf("%s: I need to write in fd: %d\n", token->cmd_stack->head, fd_io[WRITE]);
//	pid = fork();
//	if (pid == -1)
//		return (-1);
//	else if (pid == 0)
//	{
//		if (token && token->next && token->next->type == PIPE)
//			close(fd_pipe[READ]);
//		errno = 0;
//		if (fd_io[READ] != fd_in)
//		{
//			dup2(fd_io[READ], fd_in);
//			close(fd_io[READ]);
//		}
//		if (fd_io[WRITE] != STDOUT_FILENO)
//		{
//			dup2(fd_io[WRITE], STDOUT_FILENO);
//			close(fd_io[WRITE]);
//		}
//		printf("I read from fd: %d\n", fd_io[READ]);
//		printf("I write in fd: %d\n", fd_io[WRITE]);
//		exit(cmd_router(token->cmd_stack, envp_dict));
//	}
//	else
//	{
//		close(fd_pipe[WRITE]);
//		if (token && token->next && token->next->type == PIPE)
//		{
//			save_in = dup(fd_in);
//			if (save_in == -1 && dup2(fd_pipe[READ], fd_in) == -1)
//				return (-1);
//			close(fd_pipe[READ]);
//			exec_pipe(token->next->next, envp_dict, fd_pipe[READ]);
//			dup2(save_in, fd_in);
//		}
//		waitpid(pid, &g_return_value, 0);
//		g_return_value = WEXITSTATUS(g_return_value);
//	}
//	return (0);
//}

int	exec_pipe(t_token *token, t_hashtable *envp_dict, int fd_pipe_in)
{
	int	pid;
	int	fd_io[2];
	int	fd_pipe[2];

	redirect_open(token->cmd_stack);
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
			exec_pipe(token->next->next, envp_dict, fd_pipe[READ]);
			close(fd_pipe[READ]);
		}
		waitpid(pid, &g_return_value, 0);
		g_return_value = WEXITSTATUS(g_return_value);
	}
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
