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
#include <stdbool.h>
#include "redirect.h"

char		*here_doc_replace_env(t_hashtable *envp_dict, char *line);
static int	here_doc(t_redirect_param *param);
static char	*ft_strjoin_endl(char *s1, char *s2);

int	here_doc_open(t_redirect_param *param)
{
	pipe(param->fd);
	if (errno)
	{
		perror("minishell: `<<'");
		return (return_errno_error());
	}
	if (here_doc(param) != 0)
	{
		perror("minishell: `<<'");
		close(param->fd[WRITE]);
		close(param->fd[READ]);
		return (return_errno_error());
	}
	return (0);
}

int	here_doc_write(t_hashtable *envp_dict, t_redirect_param *redirect_param)
{
	redirect_param->body = here_doc_replace_env(envp_dict, redirect_param->body);
	if (redirect_param->body == NULL)
		return (return_errno_error());
	if (*redirect_param->body != 0)
		ft_putendl_fd(redirect_param->body, redirect_param->fd[WRITE]);
	close(redirect_param->fd[WRITE]);
	return (0);
}

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

static int	here_doc(t_redirect_param *param)
{
	char	*delimiter;
	char	*prompt;
	char	*tmp;
	bool	end;

	delimiter = param->body;
	param->body = NULL;
	end = false;
	prompt = ft_strjoin(delimiter, " > ");
	if (errno)
	{
		free(delimiter);
		return (return_errno_error());
	}
	while (end == false)
	{
		tmp = readline(prompt);
		if (tmp == NULL)
		{
			free(prompt);
			free(delimiter);
			return (return_errno_error());
		}
		errno = 0;
		if (ft_strcmp(tmp, delimiter) == 0)
			end = true;
		else
		{
			param->body = ft_strjoin_endl(param->body, tmp);
			if (errno)
			{
				free(prompt);
				free(delimiter);
				return (return_errno_error());
			}
		}
		free(tmp);
	}
	free(prompt);
	free(delimiter);
	return (0);
}

static char	*ft_strjoin_endl(char *s1, char *s2)
{
	char	*new;
	size_t	len_s1;
	size_t	len_s2;

	len_s2 = ft_strlen(s2);
	if (s1 == NULL)
		return (ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	new = (char *) malloc(sizeof(char) * (len_s1 + len_s2 + 2));
	if (new == NULL)
		return (NULL);
	ft_memcpy((void *) new, (void *) s1, len_s1);
	new[len_s1] = '\n';
	ft_strlcpy(&(new[len_s1 + 1]), s2, len_s2 + 1);
	free(s1);
	return (new);
}
