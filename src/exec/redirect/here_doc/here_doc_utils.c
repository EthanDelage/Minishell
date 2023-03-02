/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:42:00 by ethan             #+#    #+#             */
/*   Updated: 2023/02/06 00:42:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

char		*here_doc_replace_env(t_hashtable *envp_dict, char *line);

void	here_doc_close(t_redirect_param *redirect_param)
{
	if (redirect_param->fd[READ] > 0)
		close(redirect_param->fd[READ]);
}

void	here_doc_close_error(t_redirect_param *redirect_param)
{
	here_doc_close(redirect_param);
	if (redirect_param->fd[WRITE] > 0)
		close(redirect_param->fd[WRITE]);
}

void	here_doc_warning(char *delimiter)
{
	printf("minishell: warning: here-document delimited by "
		"end-of-file (wanted `%s')\n", delimiter);
}

void	here_doc_close_all(t_token *head, t_token *delimiter)
{
	t_cmd_token	*current;

	while (head != delimiter)
	{
		if (head->type == COMMAND)
		{
			current = head->cmd_stack;
			while (current)
			{
				if (current->type == HERE_DOC)
					here_doc_close((t_redirect_param *) current->body);
				current = current->next;
			}
		}
		head = head->next;
	}
}

int	here_doc_write_from_input(t_hashtable *envp_dict, int fd_read,
		int fd_pipe_write)
{
	char	*tmp;

	tmp = get_next_line(fd_read);
	if (errno)
		return (FAILURE);
	while (tmp)
	{
		tmp = here_doc_replace_env(envp_dict, tmp);
		if (tmp == NULL)
			return (FAILURE);
		ft_putstr_fd(tmp, fd_pipe_write);
		free(tmp);
		tmp = get_next_line(fd_read);
		if (errno)
			return (FAILURE);
	}
	return (SUCCESS);
}
