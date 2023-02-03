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

extern unsigned char	g_return_value;

static int	exec_cmd_bin(t_token *cmd_token, int fd_io[2],
				t_hashtable *envp_dict);
static void	exec_cmd_builtin(t_token *cmd_token, int fd_io[2],
				t_hashtable *envp_dict);

t_token	*exec_cmd(t_token *head, t_hashtable *envp_dict)
{
	int	fd_io[2];

	if (replace(envp_dict, head->cmd_stack) == EXIT_FAILURE)
	{
		g_return_value = 2;
		return (NULL);
	}
	if (exec_set_fd_io(head->cmd_stack, fd_io, envp_dict) == EXIT_FAILURE)
	{
		g_return_value = 1;
		return (head->next);
	}
	if (is_builtin(head->cmd_stack) == 0)
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

	pid = fork();
	if (pid == -1)
		return (2);
	else if (pid == 0)
	{
		if (fd_io[READ] != STDIN_FILENO)
		{
			if (dup2_save_fd(fd_io[READ], STDIN_FILENO) == -1)
			{
				redirect_close(cmd_token->cmd_stack);
				exit(g_return_value);
			}
		}
		if (fd_io[WRITE] != STDOUT_FILENO)
		{
			if (dup2_save_fd(fd_io[WRITE], STDOUT_FILENO) == -1)
			{
				redirect_close(cmd_token->cmd_stack);
				exit(g_return_value);
			}
		}
		redirect_close(cmd_token->cmd_stack);
		cmd_router(cmd_token, envp_dict);
	}
	else
		waitpid(pid, &return_value, 0);
	return (WEXITSTATUS(return_value));
}

static void	exec_cmd_builtin(t_token *cmd_token, int fd_io[2],
				t_hashtable *envp_dict)
{
	int	fd_save[2];

	fd_save[READ] = -1;
	fd_save[WRITE] = -1;
	if (fd_io[READ] != STDIN_FILENO)
	{
		fd_save[READ] = dup2_save_fd(fd_io[READ], STDIN_FILENO);
		if (fd_save[READ] == -1)
		{
			redirect_close(cmd_token->cmd_stack);
			return ;
		}
	}
	if (fd_io[WRITE] != STDOUT_FILENO)
	{
		fd_save[WRITE] = dup2_save_fd(fd_io[WRITE], STDOUT_FILENO);
		if (fd_save[WRITE] == -1)
		{
			redirect_close(cmd_token->cmd_stack);
			return ;
		}
	}
	redirect_close(cmd_token->cmd_stack);
	g_return_value = exec_builtin(cmd_token, envp_dict);
	if (fd_save[READ] != -1 && fd_save[READ] != STDIN_FILENO)
	{
		if (dup2_save_fd(fd_save[READ], STDIN_FILENO) == -1)
			return ;
		close(fd_save[READ]);
	}
	if (fd_save[WRITE] != -1 && fd_save[WRITE] != STDOUT_FILENO)
	{
		if (dup2_save_fd(fd_save[WRITE], STDOUT_FILENO) == -1)
			return ;
		close(fd_save[WRITE]);
	}
}
