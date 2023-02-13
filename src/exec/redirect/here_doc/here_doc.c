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
static char	*here_doc_get_input(char *delimiter, char *prompt);

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
	return (SUCCESS);
}

int	here_doc_write(t_hashtable *envp_dict, t_redirect_param *redirect_param)
{
	redirect_param->body = here_doc_replace_env(envp_dict,
			redirect_param->body);
	if (redirect_param->body == NULL)
		return (return_errno_error());
	if (*redirect_param->body != 0)
		ft_putendl_fd(redirect_param->body, redirect_param->fd[WRITE]);
	close(redirect_param->fd[WRITE]);
	return (SUCCESS);
}

static int	here_doc(t_redirect_param *param)
{
	char	*delimiter;
	char	*prompt;

	delimiter = param->body;
	prompt = ft_strjoin(delimiter, " > ");
	if (errno)
	{
		free(delimiter);
		return (return_errno_error());
	}
	param->body = here_doc_get_input(delimiter, prompt);
	free(delimiter);
	free(prompt);
	if (!errno && param->body == NULL)
		param->body = ft_calloc(1, sizeof(char));
	if (errno)
		return (return_errno_error());
	return (SUCCESS);
}

static char	*here_doc_get_input(char *delimiter, char *prompt)
{
	bool	end;
	char	*tmp;
	char	*result;

	result = NULL;
	end = false;
	while (end == false)
	{
		tmp = readline(prompt);
		if (errno)
			return (NULL);
		else if (tmp == NULL)
			return (here_doc_warning(result, delimiter));
		if (ft_strcmp(tmp, delimiter) == 0)
			end = true;
		else
		{
			result = ft_strjoin_endl(result, tmp);
			if (errno)
			{
				free(tmp);
				return (NULL);
			}
		}
		free(tmp);
	}
	return (result);
}
