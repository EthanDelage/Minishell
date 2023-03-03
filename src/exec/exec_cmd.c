/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:22:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/26 01:22:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "exec.h"

static int	exec_cmd_bin(t_token *cmd_token, int fd_io[2],
				t_hashtable *envp_dict);
static void	exec_cmd_bin_fork(t_hashtable *envp_dict, t_token *cmd_token,
				int fd_io[2]);
static void	exec_cmd_builtin(t_token *cmd_token, int fd_io[2],
				t_hashtable *envp_dict);
static int	builtin_set_fd(int new_fd, int old_fd);

t_token	*exec_cmd(t_token *head, t_hashtable *envp_dict)
{
	int	fd_io[2];

	if (replace(envp_dict, head->cmd_stack) == EXIT_FAILURE)
	{
		g_return_value = 1;
		return (NULL);
	}
	if (head->cmd_stack == NULL || head->cmd_stack->body == NULL)
	{
		g_return_value = 0;
		return (head->next);
	}
	if (exec_set_fd_io(head->cmd_stack, fd_io, envp_dict) == EXIT_FAILURE)
		return (head->next);
	if (head->cmd_stack->type != COMMAND)
		g_return_value = 0;
	else if (is_builtin(head->cmd_stack) == 0)
		g_return_value = exec_cmd_bin(head, fd_io, envp_dict);
	else
		exec_cmd_builtin(head, fd_io, envp_dict);
	return (head->next);
}

static int	exec_cmd_bin(t_token *cmd_token, int fd_io[2],
				t_hashtable *envp_dict)
{
	pid_t	pid;
	int		return_value;

	return_value = 0;
	pid = fork();
	if (pid == -1)
		return (errno);
	else if (pid == 0)
		exec_cmd_bin_fork(envp_dict, cmd_token, fd_io);
	else
	{
		if (is_exec_minishell(cmd_token->cmd_stack->head))
			if (sig_ignore() == FAILURE)
				g_return_value = errno;
		waitpid(pid, &return_value, 0);
	}
	if (fd_io[WRITE] != STDOUT_FILENO)
		close(fd_io[WRITE]);
	if (fd_io[READ] != STDIN_FILENO)
		close(fd_io[READ]);
	if (WIFSIGNALED(return_value) && (WTERMSIG(return_value) == SIGINT
			|| WTERMSIG(return_value) == SIGQUIT))
		return (g_return_value);
	return (WEXITSTATUS(return_value));
}

static void	exec_cmd_bin_fork(t_hashtable *envp_dict, t_token *cmd_token,
				int fd_io[2])
{
	if (init_sigaction(sig_handler_cmd_fork) == FAILURE)
		exit(errno);
	exec_fork_set_fd_io(fd_io);
	exit(cmd_router(cmd_token, envp_dict));
}

static void	exec_cmd_builtin(t_token *cmd_token, int fd_io[2],
				t_hashtable *envp_dict)
{
	int	fd_save[2];

	fd_save[READ] = -1;
	fd_save[WRITE] = -1;
	if (fd_io[READ] != STDIN_FILENO)
	{
		fd_save[READ] = builtin_set_fd(fd_io[READ], STDIN_FILENO);
		if (fd_save[READ] == -1)
			return ;
	}
	if (fd_io[WRITE] != STDOUT_FILENO)
	{
		fd_save[WRITE] = builtin_set_fd(fd_io[WRITE], STDOUT_FILENO);
		if (fd_save[WRITE] == -1)
		{
			if (fd_save[READ] != -1)
				if (dup2_fd(fd_save[READ], STDIN_FILENO) == EXIT_FAILURE)
					close(fd_save[READ]);
			return ;
		}
	}
	g_return_value = exec_builtin(cmd_token, envp_dict);
	reset_stdio(fd_save);
}

static int	builtin_set_fd(int new_fd, int old_fd)
{
	int	save_fd;

	save_fd = dup(old_fd);
	if (save_fd == -1)
	{
		close(new_fd);
		return (-1);
	}
	if (dup2_fd(new_fd, old_fd) == EXIT_FAILURE)
	{
		close(new_fd);
		close(save_fd);
		return (-1);
	}
	return (save_fd);
}
