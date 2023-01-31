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

int	exec_cmd(t_token *token, t_hashtable *envp_dict)
{
	int		return_val;
	int		fd_io[2];
	pid_t	pid;
	int		fd_save[2];

	if (replace(envp_dict, token->cmd_stack) == 1)
		return (1);
	if (redirect_open(envp_dict, token->cmd_stack) == EXIT_FAILURE)
		return (1);
	fd_io[READ] = redirect_get_input_fd(token->cmd_stack);
	if (fd_io[READ] == -1)
		fd_io[READ] = STDIN_FILENO;
	fd_io[WRITE] = redirect_get_output_fd(token->cmd_stack);
	if (fd_io[WRITE] == -1)
		fd_io[WRITE] = STDOUT_FILENO;
	if (fd_io[READ] != STDIN_FILENO)
	{
		fd_save[READ] = dup(STDIN_FILENO);
		dup2(fd_io[READ], STDIN_FILENO);
		close(fd_io[READ]);
	}
	if (fd_io[WRITE] != STDOUT_FILENO)
	{
		fd_save[WRITE] = dup(STDOUT_FILENO);
		dup2(fd_io[WRITE], STDOUT_FILENO);
		close(fd_io[WRITE]);
	}
	if (is_builtin(token->cmd_stack, envp_dict) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			errno = 0;
			if (ft_strchr(token->cmd_stack->head, '/') != NULL)
				exec_path(token->cmd_stack, envp_dict);
			else
				exec_bin(token->cmd_stack, envp_dict);
		}
		else
		{
			waitpid(pid, &return_val, 0);
			g_return_value = WEXITSTATUS(return_val);
		}
	}
	else
		g_return_value = exec_builtin(token, envp_dict);
	if (redirect_get_input_fd(token->cmd_stack) != -1)
	{
		dup2(fd_save[READ], STDIN_FILENO);
		close(fd_save[READ]);
	}
	if (redirect_get_output_fd(token->cmd_stack) != -1)
	{
		dup2(fd_save[WRITE], STDOUT_FILENO);
		close(fd_save[WRITE]);
	}
	return (EXIT_SUCCESS);
}
