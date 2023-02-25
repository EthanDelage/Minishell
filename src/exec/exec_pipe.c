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

static pid_t	exec_pipe_cmd(t_token *head, t_hashtable *envp_dict,
					int fd_in, int fd_pipe[2]);
static void		exec_pipe_cmd_fork(t_hashtable *envp_dict, t_token *head,
					int fd_io[2], int fd_pipe[2]);
static void		exec_pipe_get_ret_val(int pid, t_token *next_cmd, t_ret_val *ret_val);
static void	set_last_ret_value(int return_value, t_ret_val *ret_val);
static void	init_ret_val(t_ret_val *ret_val);

t_token	*exec_pipe(t_token **head, t_hashtable *envp_dict, int fd_in)
{
	pid_t				pid;
	int					fd_pipe[2];
	t_token				*next_cmd;
	static t_ret_val	ret_val;

	if (fd_in == STDIN_FILENO)
		init_ret_val(&ret_val);
	next_cmd = get_next_pipe(*head);
	if (next_cmd && pipe(fd_pipe) == -1)
		return (NULL);
	else if (next_cmd == NULL)
		fd_pipe[WRITE] = -1;
	if ((*head)->type == OPEN_PARENTHESIS)
		pid = exec_pipe_subshell(head, envp_dict, fd_in, fd_pipe);
	else
		pid = exec_pipe_cmd(*head, envp_dict, fd_in, fd_pipe);
	if (pid == -1 && errno)
		return (NULL);
	if (next_cmd)
	{
		close(fd_pipe[WRITE]);
		exec_pipe(&next_cmd, envp_dict, fd_pipe[READ]);
		close(fd_pipe[READ]);
	}
	if (pid != -1)
		exec_pipe_get_ret_val(pid, next_cmd, &ret_val);
	return (get_next_cmd(*head));
}

static pid_t	exec_pipe_cmd(t_token *head, t_hashtable *envp_dict,
					int fd_in, int fd_pipe[2])
{
	pid_t				pid;
	int					fd_io[2];

	fd_io[READ] = fd_in;
	if (replace(envp_dict, head->cmd_stack) == FAILURE || exec_pipe_set_fd_io(
			head->cmd_stack, fd_io, fd_pipe[WRITE], envp_dict) == FAILURE)
	{
		g_return_value = 1;
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		if (fd_pipe[WRITE] != -1)
			close_pipe(fd_pipe);
		g_return_value = errno;
		return (-1);
	}
	else if (pid == 0)
		exec_pipe_cmd_fork(envp_dict, head, fd_io, fd_pipe);
	if (fd_io[READ] != fd_in && fd_io[READ] != STDIN_FILENO)
		close(fd_io[READ]);
	if (fd_io[WRITE] != fd_pipe[WRITE] && fd_io[WRITE] != STDOUT_FILENO)
		close(fd_io[WRITE]);
	return (pid);
}

static void	exec_pipe_cmd_fork(t_hashtable *envp_dict, t_token *head,
				int fd_io[2], int fd_pipe[2])
{
	if (init_sigaction(sig_handler_cmd_fork) == FAILURE)
		exit(errno);
	if (fd_pipe[WRITE] != -1)
	{
		close(fd_pipe[READ]);
		if (fd_io[WRITE] != fd_pipe[WRITE])
			close(fd_pipe[WRITE]);
	}
	if (fd_io[READ] != STDIN_FILENO)
		if (dup2_fd(fd_io[READ], STDIN_FILENO) == EXIT_FAILURE)
			exit(errno);
	if (fd_io[WRITE] != STDOUT_FILENO)
		if (dup2_fd(fd_io[WRITE], STDOUT_FILENO) == EXIT_FAILURE)
			exit(errno);
	exit(cmd_router(head, envp_dict));
}

static void	exec_pipe_get_ret_val(int pid, t_token *next_cmd, t_ret_val *ret_val)
{
	int			return_value;

	waitpid(pid, &return_value, 0);
	if (next_cmd == NULL)
		set_last_ret_value(return_value, ret_val);
	if (ret_val->last_cmd_sig == false && ret_val->ret_val != -1)
		g_return_value = ret_val->ret_val;
}

static void	set_last_ret_value(int return_value, t_ret_val *ret_val)
{
	if (WIFSIGNALED(return_value))
		ret_val->last_cmd_sig = true;
	if (WIFSIGNALED(return_value) && (WTERMSIG(return_value) == SIGINT
			|| WTERMSIG(return_value) == SIGQUIT))
		ret_val->ret_val = g_return_value;
	else
		ret_val->ret_val = WEXITSTATUS(return_value);
}

static void	init_ret_val(t_ret_val *ret_val)
{
	ret_val->ret_val = -1;
	ret_val->last_cmd_sig = false;
}