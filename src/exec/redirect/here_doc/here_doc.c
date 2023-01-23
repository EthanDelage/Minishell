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
#include <readline/readline.h>
#include "redirect.h"

char		*replace(t_hashtable *envp_dict, char *line);
static int	here_doc(int fd, char *delimiter, t_hashtable *envp_dict);

int	here_doc_open(t_hashtable *envp_dict, t_redirect_param *redirect_param)
{
	pipe(redirect_param->fd);
	if (errno)
		return (errno);
	here_doc(redirect_param->fd[WRITE], redirect_param->body, envp_dict);
	if (errno)
		return (errno);
	close(redirect_param->fd[WRITE]);
	redirect_param->fd[WRITE] = -1;
	return (0);
}

void	here_doc_close(t_redirect_param *redirect_param)
{
	close(redirect_param->fd[WRITE]);
}

static int	here_doc(int fd, char *delimiter, t_hashtable *envp_dict)
{
	char	*line;

	line = readline("> ");
	if (ft_strcmp(line, delimiter) != 0)
		ft_putendl_fd(line, fd);
	while (ft_strcmp(line, delimiter) != 0)
	{
		free(line);
		line = readline("> ");
		if (line == NULL)
			return (errno);
		errno = 0;
		line = replace(envp_dict, line);
		if (errno)
			return (errno);
		if (ft_strcmp(line, delimiter) != 0)
			ft_putendl_fd(line, fd);
	}
	free(line);
	return (0);
}
