/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:30:09 by edelage           #+#    #+#             */
/*   Updated: 2023/02/01 22:30:10 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "exec.h"

extern unsigned char	g_return_value;

static void	exec_get_fd_io(t_cmd_token *head, int fd_io[2]);

int	exec_pipe_set_fd_io(t_cmd_token *head, int fd_io[2], int fd_out_pipe,
		t_hashtable *envp_dict)
{
	fd_io[READ] = STDIN_FILENO;
	fd_io[WRITE] = fd_out_pipe;
	if (redirect_open(envp_dict, head) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exec_get_fd_io(head, fd_io);
	return (EXIT_SUCCESS);
}

int	exec_set_fd_io(t_cmd_token *head, int fd_io[2], t_hashtable *envp_dict)
{
	fd_io[READ] = STDIN_FILENO;
	fd_io[WRITE] = STDOUT_FILENO;
	if (redirect_open(envp_dict, head) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exec_get_fd_io(head, fd_io);
	return (EXIT_SUCCESS);
}

static void	exec_get_fd_io(t_cmd_token *head, int fd_io[2])
{
	while (head)
	{
		if (head->type == REDIRECT_OUT || head->type == APPEND_OUT)
			fd_io[WRITE] = ((t_redirect_param *) head->body)->fd[WRITE];
		else if (head->type == REDIRECT_IN || head->type == HERE_DOC)
			fd_io[READ] = ((t_redirect_param *) head->body)->fd[READ];
		head = head->next;
	}
}

int	dup2_save_fd(int new_fd, int old_fd)
{
	int	save_fd;

	save_fd = dup(old_fd);
	printf("%d\n", save_fd);
	if (save_fd == -1 || dup2(new_fd, old_fd) == -1)
	{
		g_return_value = errno;
		perror("minishell");
		errno = 0;
		return (-1);
	}
	return (save_fd);
}
