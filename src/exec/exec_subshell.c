/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:06:27 by edelage           #+#    #+#             */
/*   Updated: 2023/02/01 22:06:29 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "exec.h"

extern unsigned char	g_return_value;

static t_token	*subshell_get_next_token(t_token *head);
static int		subshell_set_fd_io(t_token *head, int fd_io[2],
					t_hashtable *envp_dict);

t_token	*exec_subshell(t_token *head, t_hashtable *envp_dict)
{
	pid_t	pid;
	int		fd_io[2];
	int		return_value;
	t_token	*next_token;

	next_token = subshell_get_next_token(head->next);
	if (subshell_set_fd_io(next_token, fd_io, envp_dict) == EXIT_FAILURE)
	{
		if (next_token && next_token->type == COMMAND)
			return (next_token->next);
		return (next_token);
	}
	pid = fork();
	if (pid == -1)
	{
		g_return_value = errno;
		return (NULL);
	}
	else if (pid == 0)
	{
		if (fd_io[READ] != STDIN_FILENO)
		{
			if (dup2_save_fd(fd_io[READ], STDIN_FILENO) == -1)
			{
				redirect_close(head->cmd_stack);
				exit(g_return_value);
			}
		}
		if (fd_io[WRITE] != STDOUT_FILENO)
		{
			if (dup2_save_fd(fd_io[WRITE], STDOUT_FILENO) == -1)
			{
				redirect_close(head->cmd_stack);
				exit(g_return_value);
			}
		}
		redirect_close(head->cmd_stack);
		exec(head->next, envp_dict);
		exit(g_return_value);
	}
	else
	{
		redirect_close(head->cmd_stack);
		waitpid(pid, &return_value, 0);
		g_return_value = WEXITSTATUS(return_value);
		if (next_token && next_token->type == COMMAND)
			return (next_token->next);
		return (next_token);
	}
}

static t_token	*subshell_get_next_token(t_token *head)
{
	size_t	count_parenthesis;

	count_parenthesis = 1;
	while (head && count_parenthesis != 0)
	{
		if (head->type == OPEN_PARENTHESIS)
			count_parenthesis++;
		else if (head->type == CLOSE_PARENTHESIS)
			count_parenthesis--;
		head = head->next;
	}
	return (head);
}

static int	subshell_set_fd_io(t_token *head, int fd_io[2], t_hashtable *envp_dict)
{
	if (head && head->type == COMMAND
		&& head->cmd_stack->type != COMMAND)
	{
		if (exec_set_fd_io(head->cmd_stack, fd_io, envp_dict) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		fd_io[READ] = STDIN_FILENO;
		fd_io[WRITE] = STDIN_FILENO;
	}
	return (EXIT_SUCCESS);
}
