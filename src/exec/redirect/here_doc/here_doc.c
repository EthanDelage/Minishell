/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/23 09:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

char		*here_doc_replace_env(t_hashtable *envp_dict, char *line);
static int	here_doc_error(int fd_pipe[2], int fd_read);
static int	here_doc(t_redirect_param *param);
static void	here_doc_get_input(t_redirect_param *param);
void		close_pipe(int fd_pipe[2]);

int	here_doc_open(t_redirect_param *param)
{
	int	ret;

	pipe(param->fd);
	if (errno)
	{
		perror("minishell: `<<'");
		return (return_errno_error());
	}
	ret = here_doc(param);
	if (ret == 130)
	{
		close_pipe(param->fd);
		return (-1);
	}
	else if (ret != 0)
	{
		perror("minishell: `<<'");
		close_pipe(param->fd);
		return (g_return_value);
	}
	close(param->fd[WRITE]);
	return (SUCCESS);
}

int	here_doc_write(t_hashtable *envp_dict, t_redirect_param *redirect_param)
{
	int		fd_pipe[2];
	char	*tmp;

	pipe(fd_pipe);
	if (errno)
	{
		close(redirect_param->fd[READ]);
		redirect_param->fd[READ] = -1;
		g_return_value = errno;
		return (FAILURE);
	}
	tmp = get_next_line(redirect_param->fd[READ]);
	if (errno)
		return (here_doc_error(fd_pipe, redirect_param->fd[READ]));
	while (tmp)
	{
		tmp = here_doc_replace_env(envp_dict, tmp);
		if (tmp == NULL)
			return (here_doc_error(fd_pipe, redirect_param->fd[READ]));
		ft_putstr_fd(tmp, fd_pipe[WRITE]);
		free(tmp);
		tmp = get_next_line(redirect_param->fd[READ]);
		if (errno)
			return (here_doc_error(fd_pipe, redirect_param->fd[READ]));
	}
	close(redirect_param->fd[READ]);
	close(fd_pipe[WRITE]);
	redirect_param->fd[READ] = fd_pipe[READ];
	return (SUCCESS);
}

static int	here_doc_error(int fd_pipe[2], int fd_read)
{
	close_pipe(fd_pipe);
	close(fd_read);
	g_return_value = 1;
	return (FAILURE);
}

static int	here_doc(t_redirect_param *param)
{
	pid_t	pid;
	int		return_value;

	pid = fork();
	if (pid == -1)
		return (errno);
	else if (pid == 0)
		here_doc_get_input(param);
	waitpid(pid, &return_value, 0);
	if (errno == EINTR)
		errno = 0;
	g_return_value = WEXITSTATUS(return_value);
	return (g_return_value);
}

static void	here_doc_get_input(t_redirect_param *param)
{
	char	*tmp;

	close(param->fd[READ]);
	if (init_sigaction(sig_handler_here_doc_fork) == FAILURE)
		exit (errno);
	while (1)
	{
		tmp = readline("here-doc > ");
		if (tmp == NULL)
		{
			here_doc_warning(param->body);
			close(param->fd[WRITE]);
			exit(0);
		}
		else if (ft_strcmp(tmp, param->body) == 0)
		{
			close(param->fd[WRITE]);
			exit(0);
		}
		else
		{
			ft_putendl_fd(tmp, param->fd[WRITE]);
			free(tmp);
		}
	}
}
