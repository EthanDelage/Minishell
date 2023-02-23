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

int	here_doc_get(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->type == COMMAND
			&& cmd_here_doc_open(current->cmd_stack) == FAILURE)
		{
			cmd_here_doc_close_error(head, current->cmd_stack);
			return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}

static int	cmd_here_doc_open(t_cmd_token *cmd_token)
{
	while (cmd_token)
	{
		if (cmd_token->type == HERE_DOC)
			if (here_doc_open((t_redirect_param *) cmd_token->body) != 0)
				return (FAILURE);
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
