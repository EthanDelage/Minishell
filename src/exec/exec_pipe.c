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
#include "exec.h"

extern unsigned char	g_return_value;

static void		close_pipe(int fd_pipe[2]);
static t_token	*exec_pipe_get_next_cmd(t_token *head);
static int		pipe_router(t_token *head, t_hashtable *envp_dict);

//t_token	*exec_pipe(t_token *head, t_hashtable *envp_dict, int fd_in)
//{
//	pid_t	pid;
//	int		fd_pipe[2];
//	int		return_value;
//	t_token	*next_cmd;
//
//	next_cmd = exec_pipe_get_next_cmd(head);
//	if (next_cmd)
//	{
//		if (pipe(fd_pipe) == -1)
//			return (NULL);
//	}
//	pid = fork();
//	if (pid == -1)
//	{
//		close_pipe(fd_pipe);
//	}
//	else if (pid == 0)
//	{
////		close(fd_pipe[READ]);
//		if (fd_in != STDIN_FILENO)
//		{
//			if (dup2_save_fd(fd_in, STDIN_FILENO) == -1)
//				return (NULL);
//			close(fd_in);
//		}
//		if (next_cmd)
//		{
//			if (dup2_save_fd(fd_pipe[WRITE], STDOUT_FILENO) == -1)
//				return (NULL);
//			close(fd_pipe[WRITE]);
//		}
//		exit(pipe_router(head, envp_dict));
//	}
//	else
//	{
////		close(fd_pipe[READ]);
//		if (next_cmd)
//		{
//			close(fd_pipe[WRITE]);
//			next_cmd = exec_pipe(next_cmd, envp_dict, fd_pipe[READ]);
//		}
//		waitpid(pid, &return_value, 0);
//		g_return_value = WEXITSTATUS(return_value);
//	}
//	return (next_cmd);
//}

t_token	*exec_pipe(t_token *head, t_hashtable *envp_dict, int fd_in)
{
	pid_t	pid;
	int 	fd_io[2];
	int 	fd_pipe[2];
	int		return_value;
	t_token	*next_cmd;

	next_cmd = exec_pipe_get_next_cmd(head);
	fd_io[READ] = fd_in;
	if (next_cmd)
	{
		if (pipe(fd_pipe) == -1)
			return (NULL);
	}
	else
		fd_pipe[WRITE] = -1;
	if (exec_pipe_set_fd_io(head->cmd_stack, fd_io, fd_pipe[WRITE], envp_dict) == EXIT_FAILURE)
	{
		close_pipe(fd_pipe);
		return (NULL);
	}
	pid = fork();
	if (pid == -1)
	{
		if (next_cmd)
			close_pipe(fd_pipe);
		redirect_close(head->cmd_stack);
		g_return_value = errno;
		return (NULL);
	}
	else if (pid == 0)
	{
		if (next_cmd)
			close(fd_pipe[READ]);
		if (fd_io[READ] != STDIN_FILENO)
		{
			if (dup2_save_fd(fd_io[READ], STDIN_FILENO) == -1)
				exit(errno);
			close(fd_io[READ]);
		}
		if (fd_io[WRITE] != STDOUT_FILENO)
		{
			if (dup2_save_fd(fd_io[WRITE], STDOUT_FILENO) == -1)
				exit(errno);
			close(fd_io[WRITE]);
		}
		exit(pipe_router(head, envp_dict));
	}
	else
	{
		redirect_close(head->cmd_stack);
		if (next_cmd)
		{
			close(fd_pipe[WRITE]);
			next_cmd = exec_pipe(next_cmd, envp_dict, fd_pipe[READ]);
			close(fd_pipe[READ]);
		}
		waitpid(pid, &return_value, 0);
		g_return_value = WEXITSTATUS(return_value);
		return (next_cmd);
	}
}


static void	close_pipe(int fd_pipe[2])
{
	close(fd_pipe[READ]);
	close(fd_pipe[WRITE]);
}

static t_token	*exec_pipe_get_next_cmd(t_token *head)
{
	size_t	count_parenthesis;

	count_parenthesis = 0;
	while (head)
	{
		if (head->type == PIPE && count_parenthesis == 0)
			return (head->next);
		else if (head->type == OPEN_PARENTHESIS)
			count_parenthesis++;
		else if (head->type == CLOSE_PARENTHESIS)
			count_parenthesis--;
		head = head->next;
	}
	return (NULL);
}

static int	pipe_router(t_token *head, t_hashtable *envp_dict)
{
	if (head->type == OPEN_PARENTHESIS)
		exec_subshell(head, envp_dict);
	else
	{
		if (replace(envp_dict, head->cmd_stack) == -1)
			return (errno);
		cmd_router(head, envp_dict);
	}
	return (g_return_value);
}
