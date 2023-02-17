/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:36:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/23 08:36:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

static char	*trim_quote_filename(t_redirect_param *param);
static int	redirect_open_one(t_hashtable *envp_dict, t_cmd_token *cmd_token);
static int	redirect_close_error(t_cmd_token *head, t_cmd_token *node_error);

/**
 * @brief Open all redirect files before executing command
 */
int	redirect_open(t_hashtable *envp_dict, t_cmd_token *cmd_token)
{
	t_cmd_token	*head;

	head = cmd_token;
	while (cmd_token)
	{
		if (cmd_token->type != COMMAND)
		{
			((t_redirect_param *) cmd_token->body)->body
				= trim_quote_filename((t_redirect_param *) cmd_token->body);
			if (errno)
				return (redirect_close_error(head, cmd_token));
			if (redirect_open_one(envp_dict, cmd_token) == FAILURE)
				return (redirect_close_error(head, cmd_token));
		}
		cmd_token = cmd_token->next;
	}
	return (SUCCESS);
}

static char	*trim_quote_filename(t_redirect_param *param)
{
	char	*tmp;

	tmp = trim_quotes(param->body);
	if (errno)
	{
		g_return_value = errno;
		errno = 0;
		return (param->body);
	}
	return (tmp);
}

static int	redirect_open_one(t_hashtable *envp_dict, t_cmd_token *cmd_token)
{
	if (cmd_token->type == REDIRECT_OUT)
		if (redirect_out_open((t_redirect_param *) cmd_token->body) != 0)
			return (FAILURE);
	if (cmd_token->type == REDIRECT_IN)
		if (redirect_in_open((t_redirect_param *) cmd_token->body) != 0)
			return (FAILURE);
	if (cmd_token->type == APPEND_OUT)
		if (append_out_open((t_redirect_param *) cmd_token->body) != 0)
			return (FAILURE);
	if (cmd_token->type == HERE_DOC)
		if (here_doc_write(envp_dict,
				(t_redirect_param *) cmd_token->body) != 0)
			return (FAILURE);
	return (SUCCESS);
}

static int	redirect_close_error(t_cmd_token *head, t_cmd_token *node_error)
{
	while (head && head != node_error)
	{
		if (head->type == REDIRECT_OUT)
			redirect_out_close((t_redirect_param *) head->body);
		if (head->type == REDIRECT_IN)
			redirect_in_close((t_redirect_param *) head->body);
		if (head->type == APPEND_OUT)
			append_out_close((t_redirect_param *) head->body);
		if (head->type == HERE_DOC)
			here_doc_close((t_redirect_param *) head->body);
		head = head->next;
	}
	return (FAILURE);
}
