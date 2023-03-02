/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:57:00 by edelage           #+#    #+#             */
/*   Updated: 2023/02/17 01:57:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

static int	cmd_here_doc_open(t_cmd_token *cmd_token);
static void	cmd_here_doc_close_error(t_token *head, t_cmd_token *node_error);
static void	here_doc_close_sigint(t_cmd_token *head, t_cmd_token *delimiter);

int	here_doc_get(t_token *head)
{
	t_token	*current;
	int		ret;

	current = head;
	while (current)
	{
		if (current->type == COMMAND)
		{
			ret = cmd_here_doc_open(current->cmd_stack);
			if (ret == FAILURE)
			{
				cmd_here_doc_close_error(head, current->cmd_stack);
				return (FAILURE);
			}
			else if (ret == -1)
			{
				here_doc_close_all(head, current);
				return (-1);
			}
		}
		current = current->next;
	}
	return (SUCCESS);
}

static int	cmd_here_doc_open(t_cmd_token *cmd_token)
{
	t_cmd_token	*head;
	int			ret;

	head = cmd_token;
	while (cmd_token)
	{
		if (cmd_token->type == HERE_DOC)
		{
			((t_redirect_param *)cmd_token->body)->body
				= trim_quotes(((t_redirect_param *)cmd_token->body)->body);
			if (errno)
				return (FAILURE);
			ret = here_doc_open((t_redirect_param *)cmd_token->body);
			if (ret != 0)
			{
				if (ret > 0)
					return (FAILURE);
				else
					return (here_doc_close_sigint(head, cmd_token), -1);
			}
		}
		cmd_token = cmd_token->next;
	}
	return (SUCCESS);
}

static void	cmd_here_doc_close_error(t_token *head, t_cmd_token *node_error)
{
	t_cmd_token	*save;
	t_cmd_token	*tmp;

	while (head)
	{
		if (head->type == COMMAND)
		{
			tmp = head->cmd_stack;
			save = tmp;
			while (tmp)
			{
				if (tmp->type == HERE_DOC)
					here_doc_close_error((t_redirect_param *) tmp->body);
				tmp = tmp->next;
			}
			if (save == node_error)
				return ;
		}
		head = head->next;
	}
}

static void	here_doc_close_sigint(t_cmd_token *head, t_cmd_token *delimiter)
{
	while (head != delimiter)
	{
		if (head->type == HERE_DOC)
			here_doc_close_error((t_redirect_param *) head->body);
		head = head->next;
	}
}
